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

	this->toErase = 0;
}

Block::~Block()
{

}

void Block::update(float deltaTime)
{
	this->totalwidth = this->scale.x * this->sprite()->width();
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);
}
