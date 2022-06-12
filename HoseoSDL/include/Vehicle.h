#pragma once

#include "main.h"
#include "Vector2D.h"

class Vehicle
{
public:
	Vehicle(float x, float y);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D* f);
	Vector2D Radian(float x, float y, float r);
	Vector2D seek(Vector2D* target);
	Vector2D arrive(Vector2D* target);
	void edges();

	Vector2D* getPos() { return pos; }
	Vector2D* getVel() { return vel; }
	float getMaxSpeed() { return maxSpeed; }

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

	double maxSpeed;
	double maxForce;
	int r;
	double radian;

};
