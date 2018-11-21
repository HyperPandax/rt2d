
/**
* This class describes block behavior.
*
* Copyright 2015 Your Name <you@yourhost.com>
*/

#include "star.h"

Star::Star() : Entity()
{
	this->addSprite("assets/star.tga");
	this->sprite()->color = RED;

}

Star::~Star()
{

}

void Star::update(float deltaTime)
{

}
