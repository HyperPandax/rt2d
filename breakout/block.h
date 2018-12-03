/**
* Copyright 2015 Your Name <you@yourhost.com>
*
* @file block.h
*
* @brief description of block behavior.
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <rt2d/entity.h>

/// @brief The block class is the Entity implementation.
class Block : public Entity
{
public:
	/// @brief Constructor
	Block();
	/// @brief Destructor
	virtual ~Block();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	int x;
	int y;
	int totalwidth;
	int totalheight;

	int toErase;

private:
	
}

#endif /* BLOCK_H */

;