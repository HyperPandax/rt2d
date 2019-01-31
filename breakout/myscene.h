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
#include <rt2d/text.h>

#include "myentity.h"
#include "block.h"
#include "star.h"
#include "bonus.h"

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
	virtual void erase();
	void checkAmountBlocks();


	virtual bool AABB(Star* A, Block* B);
	virtual bool AABC(Star* A, MyEntity* B);
	virtual bool AABD(Bonus* A, MyEntity* B);

	virtual void giveBonus();
	
private:
	/// @brief the rotating square in the middle of the screen
	MyEntity* myentity;
	Star* mystar;
	Star* mystar2;

	Star* pausede;
	Star* dead;
	Star* won;

	std::vector<Block*> blocks;
	Block* b;

	std::vector<Text*> blockNr;
	Text* numt;

	std::vector<Bonus*> bonuses;
	Bonus* bs;
	
	int posa;
	int posb;

	int toTurn;

	bool paused;
	bool finishedD;
	bool finishedW;
	//Vector2 vel;

	int blocksSize;
	

	Star* star1;
	Star* star2;
	Star* star3;
	//Bonus* bonus1;
	/// @brief a Timer to rotate the color every n seconds
	Timer t;

	//timers bonus
	Timer ax;
	Timer bx;
	Timer cx;
	Timer dx;

	//bool paused;
	bool gameOver;
};

#endif /* SCENE00_H */
