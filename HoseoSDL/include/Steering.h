#pragma once

#include "main.h"
#include "Vector2D.h"
#include <vector>
#include <BaseGame.h>

class Steering
{
public:
	Steering(float x, float y);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D* f);
	Vector2D Radian(float x, float y, float r);
	Vector2D seek(Vector2D* target);
	Vector2D arrive(Vector2D* target);
	void edges();

	Vector2D GetHidingPosition(Vector2D* posOb
		, double radiusOb
		, Vector2D* posHunter);
	Vector2D Hide(Vehicle* hunter
		, std::vector<BaseGame*>obstacles);
	Vector2D Evade(Vehicle* pursuer);
	Vector2D Flee(Vector2D* TargetPos);

private:
	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;
	Vector2D* force;

	Vector2D* r1;
	Vector2D* r2;
	Vector2D* r3;
	Vector2D* rotate;
	Vector2D* Desir;
	Vector2D* Zero;

	Vector2D* ToOb;

	Vector2D* ToTarget;
	Vector2D* DesiredVel;

	Vector2D* Topursuer;
	Vector2D* VelTime;

	Vector2D* Hiding;
	Vector2D* Distance;
	Vector2D* BestHiding;

	double maxSpeed;
	double maxForce;
	int r;
	double radian;

};