#include "Walker.h"
#include <random>
#include "InputHandler.h"


Walker::Walker() 
{
	steering = new Vector2D(0, 0);
	Dir = new Vector2D(0, 0);
	vehicle = new Vehicle(100, 100);
	m_steering = new Steering(200, 200);
	Force = new Vector2D(0, 0);
	
	m_base.push_back(new BaseGame(300, 300, 32));

}

void Walker::update() 
{
	*steering = vehicle->arrive(Dir);
	vehicle->applyForce(steering);
	vehicle->update();

	*Force = m_steering->Hide(vehicle, m_base);
	m_steering->applyForce(Force);
	m_steering->update();


	m_base[0]->update();

	Dir = TheInputHandler::Instance()->getMousePosition();
}

void Walker::draw(SDL_Renderer* renderer)
{
	m_base[0]->draw(renderer);
	vehicle->draw(renderer);
	m_steering->draw(renderer);
	
}
