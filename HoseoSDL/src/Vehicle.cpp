#include "Vehicle.h"
#include "math.h"
#include "iostream"

const int WIDTH = 600;
const int HEIGHT = 400;

Vehicle::Vehicle(float x, float y): maxSpeed(6), maxForce(0.4)
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
}

void Vehicle::draw(SDL_Renderer* renderer)
{
	filledTrigonRGBA(renderer, r1->getX() + pos->getX(), r1->getY() + pos->getY()
		, r2->getX() + pos->getX(), r2->getY() + pos->getY(),
		r3->getX() + pos->getX(), r3->getY() + pos->getY(),
		255,255,255,255);
}

void Vehicle::update()
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

void Vehicle::applyForce(Vector2D* f)
{
	*acc += *f;
}

Vector2D Vehicle::Radian(float x, float y, float r)
{
	rotate = new Vector2D(0, 0);

	rotate->setX(cos(radian) * x - sin(radian) * y);
	rotate->setY(sin(radian) * x + cos(radian) * y);

	return *rotate;
}

Vector2D Vehicle::seek(Vector2D* target)
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

Vector2D Vehicle::arrive(Vector2D* target)
{
	return seek(target);
}

void Vehicle::edges()
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
