/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "myentity.h"
#include "block.h"
#include "star.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	virtual void spawnBlocks();
	virtual void bouncePlatform();
	virtual void erase();

	bool AABB(Star* A, Block* B);
	bool AABC(Star* A, MyEntity* B);

private:
	/// @brief the rotating square in the middle of the screen
	MyEntity* myentity;
	Star* mystar;
	std::vector<Block*> blocks;
	Block* b;
	int posa;
	int posb;

	int toTurn;
	
	/// @brief a Timer to rotate the color every n seconds
	Timer t;
};

#endif /* SCENE00_H */
