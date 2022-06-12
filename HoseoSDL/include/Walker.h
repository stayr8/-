#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include "BaseGame.h"
#include "Steering.h"
#include <vector>

class Walker 
{
public:
  Walker();
  void draw(SDL_Renderer* renderer);
  void update();

private:
	Vehicle* vehicle;
	Steering* m_steering;
	std::vector<BaseGame*> m_base;

	Vector2D* steering;
	Vector2D* Dir;
	Vector2D* Force;

};