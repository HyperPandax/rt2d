/**
* This class describes block behavior.
*
* Copyright 2015 Your Name <you@yourhost.com>
*/

#include "bonus.h"

Bonus::Bonus() : Entity()
{
	this->addSprite("assets/dot.tga");
	this->scale = Point(0.5f, 0.5f);
	this->velocity = Vector2(0, 0);

	this->num = 0;
	/*
	this->startPosition = Vector2(SWIDTH / 2, 600);
	this->position = startPosition;
	this->sprite()->color = RED;

	this->hearts = 3;*/
	this->toErase = 0;
	this->paused = false;

	this->totalwidth = this->scale.x * this->sprite()->width();
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);

	this->r = totalwidth / 2;
}

Bonus::~Bonus()
{

}

void Bonus::update(float deltaTime)
{

	if (input()->getKeyUp(KeyCode::Escape)) {
		if (!this->paused) {
			this->paused = true;

		}
		else {
			this->paused = false;
		}
	}

	if (this->paused) {
		return;
	}


	this->totalwidth = this->scale.x * this->sprite()->width();
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);

	this->r = totalwidth / 2;
	
	this->position += this->velocity * deltaTime;

}

int Bonus::extraLife(int i) {
	i += 1;
	return i ;
}

void Bonus::biggerPlatform(Entity* e) {
	e->scale = Point(1.5f, 0.2f);
}

