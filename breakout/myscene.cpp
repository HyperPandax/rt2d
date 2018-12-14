/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <vector>

#include "myscene.h"
#include "block.h"
#include "star.h"



MyScene::MyScene() : Scene()
{
	
	// start the timer.
	t.start();
	
	//vel = Vector2(-250, -200);

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH / 2, 700);
	myentity->scale = Point(1.0f, 0.1f);

	//mystar instance
	mystar = new Star();
	mystar->hearts = 3;
	//mystar->velocity = Vector2(0, 0);
	std::cout << mystar->hearts << std::endl;
	

	//lives
	star1 = new Star();
	star2 = new Star();
	star3 = new Star();

	star1->position = Point2(SWIDTH / 40 * 1, SHEIGHT / 20 * 19);
	star2->position = Point2(SWIDTH / 40 * 2, SHEIGHT / 20 * 19);
	star3->position = Point2(SWIDTH / 40 * 3, SHEIGHT / 20 * 19);
	star1->velocity = Vector2(0, 0);
	star2->velocity = Vector2(0, 0); 
	star3->velocity = Vector2(0, 0);
	star1->scale = Point(0.08f, 0.08f);
	star2->scale = Point(0.08f, 0.08f);
	star3->scale = Point(0.08f, 0.08f);
	star2->sprite()->color = ORANGE;
	star3->sprite()->color = YELLOW;
	


	//vector of blocks
	blocks = std::vector<Block*>();
	//spawn the blocks
	spawnBlocks();

	this->toTurn = 0;

	// create the scene 'tree'
	// add myentity & mystar to this Scene as a child.
	this->addChild(star1);
	this->addChild(star2);
	this->addChild(star3);

	this->addChild(myentity);
	this->addChild(mystar);

	this->paused = false;
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(myentity);
	this->removeChild(mystar);
	this->removeChild(star1);
	this->removeChild(star2);
	this->removeChild(star3);

	// delete myentity & mystar from the heap (there was a 'new' in the constructor)
	delete myentity;
	delete mystar;
	delete star1;
	delete star2;
	delete star3;
}

void MyScene::update(float deltaTime)
{
	
	//press esc pauses scene toggle
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
	
	//rotation color star & platform
	if (t.seconds() > 0.0333f) {
		RGBAColor color = myentity->sprite()->color;
		myentity->sprite()->color = Color::rotate(color, 0.01f);
		RGBAColor color2 = mystar->sprite()->color;
		mystar->sprite()->color = Color::rotate(color2, 0.01f);
		
		t.start();

	}

	//movement platform
	if (myentity->position.x >= 64 && myentity->position.x <= 1216) {
		if (input()->getKey(KeyCode::Left)) {
			if (input()->getKey(KeyCode::LeftShift)) {
				myentity->position.x -= 1000 * deltaTime;
			}
			myentity->position.x -= 300 * deltaTime;
		}
		if (input()->getKey(KeyCode::Right)) {
			if (input()->getKey(KeyCode::LeftShift)) {
				myentity->position.x += 1000 * deltaTime;
			}
			myentity->position.x += 300 * deltaTime;
		}
	}
	
	//makes sure the platform doesn't get stuck on the sides
	if (myentity->position.x <= 64 ) {
		myentity->position.x += 10;
	}
	if (myentity->position.x >= 1216) {
		myentity->position.x -= 10;
	}

	//erase blocks who are hit
	erase();

	//if star hits platform bounce
	if (AABC(this->mystar, this->myentity)) {
		this->mystar->turny();
		mystar->position.y -= 10;


	}

	//if star hits block bounce and toErase to 1
	for (int i = 0; i < blocks.size(); i++) {
		if (AABB(this->mystar, this->blocks[i])) {			
			b = blocks[i];
			b->toErase = 1;
		}
	}
	
	if (this->toTurn == 2) {
		mystar->turny();
		toTurn = 0;
	}
	
	

	//game paused when u die
	if (mystar->hearts <= 0) {
		
		mystar->velocity = Vector2(0, 0);
		this->removeChild(star1);
		std::cout << "Game Over" << std::endl;
	}
	if (mystar->hearts <= 2) {
		this->removeChild(star3);
	}
	if (mystar->hearts <= 1) {
		this->removeChild(star2);
	}
}

void MyScene::spawnBlocks() {
	for (int i = 0; i <55; i++) {
		if (i <= 10) {
			Block* b = new Block();
			b->sprite()->color = RED;
			b->position = Point2(SWIDTH / 12 * (1 + i), SHEIGHT / 16 * 1);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);
		}if (i <= 21 && i > 10) {
			Block* b = new Block();
			b->sprite()->color = ORANGE;
			b->position = Point2(SWIDTH / 12 * (1 + (i-11)), SHEIGHT / 16 * 2);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);
		}if (i <= 32 && i > 21) {
			Block* b = new Block();
			b->sprite()->color = YELLOW;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 22)), SHEIGHT / 16 * 3);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);
		}if (i <= 43 && i > 32) {
			Block* b = new Block();
			b->sprite()->color = GREEN;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 33)), SHEIGHT / 16 * 4);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);
		}if (i <= 55 && i > 43) {
			Block* b = new Block();
			b->sprite()->color = BLUE;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 44)), SHEIGHT / 16 * 5);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);
		}		
	}
}

bool MyScene::AABB(Star* A, Block* B) {
	if (A->x + A->totalwidth >= B->x &&
		B->x + B->totalwidth >= A->x &&
		A->y + A->totalheight >= B->y &&
		B->y + B->totalheight >= A->y
		) {
		this->toTurn = 2;
		
		return true;
	}
	else {
		return false;
	}
}

bool MyScene::AABC(Star* A, MyEntity* B) {
	if (A->x + A->totalwidth >= B->x &&
		B->x + B->totalwidth >= A->x &&
		A->y + A->totalheight >= B->y &&
		B->y + B->totalheight >= A->y
		) {
		return true;
	}
	else {
		return false;
	}
}

void MyScene::erase() {
	for (auto it = blocks.begin(); it != blocks.end();) {
		if ((*it)->toErase >= 1) {
			removeChild(*it);
			delete(*it);
			it = blocks.erase(it);
		}
		else {
			++it;
		}
		
	}
}

