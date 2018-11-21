/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
#include "block.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	spawnBlocks();

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 11);
	myentity->scale = Point(0.5f, 0.1f);

	
	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(myentity);
	this->addChild(block1);
	this->addChild(block2);
	this->addChild(block3);
	this->addChild(block4);
	this->addChild(block5);
	this->addChild(block6);
	this->addChild(block7);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(myentity);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete myentity;
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
		t.start();
	}
	//only 1 timer works at the same time bc it resets
	/*if (t.seconds() > 0.0333f) {
		RGBAColor color = block1->sprite()->color;
		block1->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
	if (t.seconds() > 0.0333f) {
		RGBAColor color = block2->sprite()->color;
		block2->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}*/

	// ###############################################################
	// move it
	// ###############################################################
	if (input()->getKey(KeyCode::Left)) {
		myentity->position.x -= 2;
	}
	if (input()->getKey(KeyCode::Right)) {
		myentity->position.x += 2;
	}
}

void MyScene::spawnBlocks() {
	block1 = new Block();
	block1->position = Point2(SWIDTH / 12 * 3, SHEIGHT / 12 * 1);
	block1->scale = Point(0.5f, 0.1f);
	block2 = new Block();
	block2->position = Point2(SWIDTH / 12 * 4, SHEIGHT / 12 * 1);
	block2->scale = Point(0.5f, 0.1f);
	block3 = new Block();
	block3->position = Point2(SWIDTH / 12 * 5, SHEIGHT / 12 * 1);
	block3->scale = Point(0.5f, 0.1f);
	block4 = new Block();
	block4->position = Point2(SWIDTH / 12 * 6, SHEIGHT / 12 * 1);
	block4->scale = Point(0.5f, 0.1f);
	block5 = new Block();
	block5->position = Point2(SWIDTH / 12 * 7, SHEIGHT / 12 * 1);
	block5->scale = Point(0.5f, 0.1f);
	block6 = new Block();
	block6->position = Point2(SWIDTH / 12 * 8, SHEIGHT / 12 * 1);
	block6->scale = Point(0.5f, 0.1f);
	block7 = new Block();
	block7->position = Point2(SWIDTH / 12 * 9, SHEIGHT / 12 * 1);
	block7->scale = Point(0.5f, 0.1f);
}