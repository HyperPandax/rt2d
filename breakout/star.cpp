
/**
* This class describes block behavior.
*
* Copyright 2015 Your Name <you@yourhost.com>
*/

#include "star.h"

Star::Star() : Entity()
{
	this->addSprite("assets/dot.tga");
	
	this->velocity = Vector2(-2.0, -2.0);
	
	this->startPosition = Vector2(SWIDTH / 2, SHEIGHT / 12 * 10);
	this->position = startPosition;
}

Star::~Star()
{

}

void Star::update(float deltaTime)
{
	
	this->position += this->velocity /* * deltaTime*/;
	//std::cout << this->position << std::endl;
	bounce();
	//std::cout << velocity << std::endl;
	
}

void Star::bounce() {
	if (this->position.x <= 0) {
		this->velocity.x *= -1;
	}
	if (this->position.y <= 0) {
		this->velocity.y *= -1;
	}
	if (this->position.x >= 1280) {
		this->velocity.x *= -1;
	}
	if (this->position.x >= 720) {
		this->velocity.y *= -1;
	}

}