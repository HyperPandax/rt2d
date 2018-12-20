/**
* Copyright 2015 Your Name <you@yourhost.com>
*
* @file block.h
*
* @brief description of block behavior.
*/

#ifndef STAR_H
#define STAR_H

#include <rt2d/entity.h>

/// @brief The block class is the Entity implementation.
class Star : public Entity
{
public:
	/// @brief Constructor
	Star();
	/// @brief Destructor
	virtual ~Star();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	virtual void bounce();
	virtual void turny();
	virtual void turnx();

	int x;
	int y;
	int r;
	int totalwidth;
	int totalheight;
	Vector2 velocity;

	Vector2 startPosition;

	int hearts;
	

private:
	/* add your private declarations */
	bool paused;
	
};

#endif /* STAR_H */
