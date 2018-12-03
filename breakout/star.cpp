
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
	
	this->startPosition = Vector2(SWIDTH / 2, 570);
	this->position = startPosition;
	this->sprite()->color = RED;

	
}

Star::~Star()
{

}

void Star::update(float deltaTime)
{
	
	this->totalwidth = this->scale.x * this->sprite()->width() ;
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);

	this->position += this->velocity * deltaTime;
	//std::cout << this->position << std::endl;
	bounce();
	//std::cout << velocity << std::endl;
	

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
	}

}

void Star::turny() {

	this->velocity.y = this->velocity.y * -1;
	
}
void Star::turnx() {

	this->velocity.x = this->velocity.x * -1;
	
}