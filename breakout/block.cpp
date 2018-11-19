/**
* This class describes block behavior.
*
* Copyright 2015 Your Name <you@yourhost.com>
*/

#include "block.h"

Block::Block() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;

}

Block::~Block()
{

}

void Block::update(float deltaTime)
{
	
}
