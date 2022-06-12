#include "Steering.h"
#include "math.h"
#include "iostream"

const int WIDTH = 600;
const int HEIGHT = 400;

Steering::Steering(float x, float y) : maxSpeed(6), maxForce(0.4)
, radian(0), r(16)
{
	pos = new Vector2D(x, y);
	vel = new Vector2D(0, 0);
	acc = new Vector2D(0, 0);
	force = new Vector2D(0, 0);
	r1 = new Vector2D(0, 0);
	r2 = new Vector2D(0, 0);
	r3 = new Vector2D(0, 0);
	rotate = new Vector2D(0, 0);
	Desir = new Vector2D(0, 0);
	Zero = new Vector2D(0, 0);

	ToOb = new Vector2D(0, 0);

	ToTarget = new Vector2D(0, 0);
	DesiredVel = new Vector2D(0, 0);

	Topursuer = new Vector2D(0, 0);
	VelTime = new Vector2D(0, 0);

	Hiding = new Vector2D(0, 0);
	Distance = new Vector2D(0, 0);
	BestHiding = new Vector2D(0, 0);
}

void Steering::draw(SDL_Renderer* renderer)
{
	filledTrigonRGBA(renderer, r1->getX() + pos->getX(), r1->getY() + pos->getY()
		, r2->getX() + pos->getX(), r2->getY() + pos->getY(),
		r3->getX() + pos->getX(), r3->getY() + pos->getY(),
		255, 255, 255, 255);
}

void Steering::update()
{
	*vel += *acc;
	vel->limit(maxSpeed);
	*pos += *vel;
	*acc *= 0;

	radian = atan2(vel->getY(), vel->getX());

	*r1 = Radian(-r, -r / 2, radian);
	*r2 = Radian(-r, r / 2, radian);
	*r3 = Radian(r, 0, radian);

	edges();
}

void Steering::applyForce(Vector2D* f)
{
	*acc += *f;
}

Vector2D Steering::Radian(float x, float y, float r)
{
	rotate = new Vector2D(0, 0);

	rotate->setX(cos(radian) * x - sin(radian) * y);
	rotate->setY(sin(radian) * x + cos(radian) * y);

	return *rotate;
}

Vector2D Steering::seek(Vector2D* target)
{
	*force = *target - *pos;
	double dist = force->length();

	if (dist > 0)
	{
		const double Decel = 1.0;
		double speed = dist / (15 * Decel);
		speed = std::min(speed, maxSpeed);
		*force *= speed;
		*force /= dist;
		Desir = force;
		*Desir -= *vel;

		return *Desir;
	}

	return *Zero;
}

Vector2D Steering::arrive(Vector2D* target)
{
	return seek(target);
}

void Steering::edges()
{
	if (pos->getX() > WIDTH + r)
	{
		pos->setX(r);
	}
	else if (pos->getX() < -r)
	{
		pos->setX(WIDTH + r);
	}

	if (pos->getY() > HEIGHT + r)
	{
		pos->setY(-r);
	}
	else if (pos->getY() < -r)
	{
		pos->setY(HEIGHT + r);
	}
}

Vector2D Steering::GetHidingPosition(Vector2D* posOb, double radiusOb, Vector2D* posHunter)
{
	double Distance = 30.0;
	double DistAway = radiusOb + Distance;

	*ToOb = *posOb - *posHunter;
	ToOb->normalize();
	*ToOb *= DistAway;
	*ToOb += *posOb;

	return *ToOb;
}

Vector2D Steering::Hide(Vehicle* hunter, std::vector<BaseGame*> obstacles)
{
	double DistToClosest = 70;

	std::vector<BaseGame*>::const_iterator curOb = obstacles.begin();
	std::vector<BaseGame*>::const_iterator closest;

	while (curOb != obstacles.end())
	{
		*Hiding = GetHidingPosition((*curOb)->getPos(), (*curOb)->getRadius(), hunter->getPos());

		*Distance = *Hiding - *pos;
		double dist = 0;
		if (dist < DistToClosest)
		{
			DistToClosest = dist;
			*BestHiding = *Hiding;
			closest = curOb;
		}
		++curOb;

	}

	if (DistToClosest == 70)
	{
		return Evade(hunter);
	}
	return arrive(BestHiding);

}

Vector2D Steering::Evade(Vehicle* pursuer)
{
	*Topursuer = *pursuer->getPos() - *pos;

	double ThreatRange = 100.0;
	if ((Topursuer->length() * Topursuer->length()) > ThreatRange * ThreatRange)
	{
		return *Zero;
	}
	double LookAheadTime = Topursuer->length() / (maxSpeed + pursuer->getMaxSpeed());

	*VelTime = *pursuer->getPos() + *pursuer->getVel() * LookAheadTime;

	return Flee(VelTime);
}

Vector2D Steering::Flee(Vector2D* TargetPos)
{
	*DesiredVel = *pos - *TargetPos;
	DesiredVel->normalize();
	*DesiredVel *= maxSpeed;
	*DesiredVel -= *vel;

	return *DesiredVel;
}
