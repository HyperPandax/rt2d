/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite("assets/block.tga");
	this->sprite()->color = RED;
	this->scale = Point(1.6f, 0.2f);

	this->startPosition = Vector2(SWIDTH / 2, 600);
	this->position = startPosition;


	this->totalwidth = this->scale.x * this->sprite()->width();
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);


	this->deg1 = Point2(-300,-100);
	this->deg2 = Point2(-300, -200);
	this->deg3 = Point2(-250, -250);
	this->deg4 = Point2(-200, -300);
	this->deg5 = Point2(-100, -300);
	this->deg6 = Point2(-50, -300);
	this->deg7 = Point2(50, -300);
	this->deg8 = Point2(100, -300);
	this->deg9 = Point2(200, -300);
	this->deg10 = Point2(250, -250);
	this->deg11 = Point2(300, -200);
	this->deg12 = Point2(300, -100);

}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	this->totalwidth = this->scale.x * this->sprite()->width();
	this->totalheight = this->scale.y * this->sprite()->width();
	this->x = this->position.x - (totalwidth / 2);
	this->y = this->position.y - (totalheight / 2);	
}
