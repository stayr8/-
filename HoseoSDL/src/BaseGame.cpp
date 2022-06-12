#include "BaseGame.h"

BaseGame::BaseGame(float x, float y, float r)
{
	pos = new Vector2D(x, y);

	_r = r;
}

void BaseGame::draw(SDL_Renderer* renderer)
{
	filledCircleRGBA(renderer, pos->getX(), pos->getY(), _r, 255, 255, 255, 255);
}

void BaseGame::update()
{

}
