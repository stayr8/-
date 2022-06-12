#pragma once

#include "main.h"


class Walker 
{
  int _x, _y;
public:
  Walker(int x, int y);
  void draw(SDL_Renderer* renderer);
  void update();
};