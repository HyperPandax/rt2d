
/**
* This class describes block behavior.
*
* Copyright 2015 Your Name <you@yourhost.com>
*/

#include "star.h"

Star::Star() : Entity()
{
	this->addSprite("assets/star.tga");
	this->scale = Point(0.15f, 0.15f);
	this->velocity = Vector2(-250.0, -200.0);
	
	this->startPosition = Vector2(SWIDTH / 2, 600);
	this->position = startPosition;
	this->sprite()->color = RED;

	this->hearts = 3;
	this->paused = false;

	this->totalwidth = this->scale.x * this->sprite()->width();
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);

	this->r = totalwidth / 2;

}

Star::~Star()
{

}

void Star::update(float deltaTime)
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

	this->totalwidth = this->scale.x * this->sprite()->width() ;
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);

	this->r = totalwidth / 2;

	this->position += this->velocity * deltaTime;
	bounce();
}

void Star::bounce() {
	if ((this->position.x > SWIDTH-15) || (this->position.x < 15)) {
		this->velocity.x = this->velocity.x * -1;
	}
	if (this->position.y < 15) {
		this->velocity.y = this->velocity.y * -1;
	}

	if(this->position.y > SHEIGHT -15) {
		
		
		
		this->velocity.y = this->velocity.y * -1;
		this->position = startPosition;
		this->hearts-=1;
	}

	// if its stuck on side
	if (this->position.x > SWIDTH - 10) {
		this->position.x -= 10;
	}
	if (this->position.y < 10) {
		this->position.y -= 10;
	}
	if (this->position.x < 10) {
		this->position.x += 10;
	}
}

void Star::turny() {
	this->velocity.y = this->velocity.y * -1;
}
void Star::turnx() {
	this->velocity.x = this->velocity.x * -1;
}