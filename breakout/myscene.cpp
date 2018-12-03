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
	
	
	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH / 2, 700);
	myentity->scale = Point(1.0f, 0.1f);

	mystar = new Star();

	//block1 = new Block();
	blocks = std::vector<Block*>();
	spawnBlocks();

	this->toTurn = 0;
	// create the scene 'tree'
	// add myentity to this Scene as a child.

	this->addChild(myentity);
	this->addChild(mystar);
	
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(myentity);
	this->removeChild(mystar);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete myentity;
	delete mystar;
}

void MyScene::update(float deltaTime)
{

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = myentity->sprite()->color;
		myentity->sprite()->color = Color::rotate(color, 0.01f);
		RGBAColor color2 = mystar->sprite()->color;
		mystar->sprite()->color = Color::rotate(color2, 0.01f);
		
		t.start();

	}
	// ###############################################################
	// move it
	// ###############################################################
	
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
		/*
		*/
	}
	if (myentity->position.x <= 64 ) {
		myentity->position.x += 10;
	}
	if (myentity->position.x >= 1216) {
		myentity->position.x -= 10;
	}
	/*this->posa = myentity->position.x - 64;
	this->posb = myentity->position.x + 64;*/


	bouncePlatform();

	erase();

	if (AABC(this->mystar, this->myentity)) {
		this->mystar->turny();
		mystar->position.y -= 10;


	}
	for (int i = 0; i < blocks.size(); i++) {
		if (AABB(this->mystar, this->blocks[i])) {
			std::cout << "works!" << std::endl;
			if (this->toTurn == 1) {
				mystar->turnx();
			}
			if (this->toTurn == 2) {
				mystar->turny();
			}
			b = blocks[i];
			b->toErase = 1;
		
			/*removeChild(b);
			delete(b);*/
			
			//this->mystar->turnx();
			//this->mystar->turny();
			
			/*b = blocks[0];
			removeChild(b);
			delete(b);
			b = blocks.erase(b);*/
		}
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

void MyScene::bouncePlatform() {
	//std::cout << "NEE" << std::endl;

	//std::cout << this->posa + this->posb << std::endl;

	/*if (mystar->position.x >= this->posa && mystar->position.x <= this->posb && mystar->position.y > 580 && mystar->position.y < 620) {
		//mystar->velocity.y = mystar->velocity.y * -1;
		mystar->turn();
		//std::cout << "haaaaaaai" << std::endl;
	}*/
	/*for (int i = 0; i < blocks.size; ) {
		if(mystar->position.x <= blocks[i]->posR){
			if (mystar->position.x >= blocks[i]->posL) {
				if (mystar->position.y >= blocks[i]->posT) {
					if (mystar->position.y <= blocks[i]->posB) {
						std::cout << "works!" << std::endl;
					}
				}
			}
		}
		i++;
	}*/


	/*for (auto it = blocks.begin(); it != blocks.end();) {
		// how to collide
		if(mystar->position.x <= (*it)->posR){
			if (mystar->position.x >= (*it)->posL) {
				if (mystar->position.y >= (*it)->posT) {
					if (mystar->position.y <= (*it)->posB) {
						removeChild(*it);
						delete(*it);
						it = blocks.erase(it);
					}
				}
			}
		}
		++it;
	}*/  


	/*for (int i = 0; i > blocks.size; i++) {
		//blocks[i];

	}*/
	/*if (mystar->position.x >= this->posL && 
		mystar->position.x <= this->posR && 
		mystar->position.y >= this->posT && 
		mystar->position.y <= this->posB) {
		
		mystar->turn();
	}*/

}


bool MyScene::AABB(Star* A, Block* B) {
	if (A->x + A->totalwidth >= B->x &&
		B->x + B->totalwidth >= A->x &&
		A->y + A->totalheight >= B->y &&
		B->y + B->totalheight >= A->y
		) {
		if (A->x + A->totalwidth >= B->x && 
			B->x + B->totalwidth >= A->x) {
			this->toTurn = 1;
		}
		if (A->y + A->totalheight >= B->y &&
			B->y + B->totalheight >= A->y) {
			this->toTurn = 2;
		}
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
