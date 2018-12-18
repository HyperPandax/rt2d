/**
* Copyright 2015 Your Name <you@yourhost.com>
*
* @file bonus.h
*
* @brief description of block behavior.
*/

#ifndef BONUS_H
#define BONUS_H

#include <rt2d/entity.h>

/// @brief The block class is the Entity implementation.
class Bonus : public Entity
{
public:
	/// @brief Constructor
	Bonus();
	/// @brief Destructor
	virtual ~Bonus();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	int extraLife(int i);
	void biggerPlatform(Entity* e);

	int x;
	int y;
	int r;
	int totalwidth;
	int totalheight;
	Vector2 velocity;

	int toErase;
	int num;

private:
	/* add your private declarations */
	bool paused;

	
};

#endif /* BONUS_H */

