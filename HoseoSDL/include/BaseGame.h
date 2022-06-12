#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"

class BaseGame
{
public:
	BaseGame(float x, float y, float r);
	void draw(SDL_Renderer* renderer);
	void update();

	Vector2D* getPos() { return pos; }
	float getRadius() { return _r; }

private:
	Vector2D* pos;

	float _r;
};