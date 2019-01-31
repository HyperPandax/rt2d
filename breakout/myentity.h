/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef MYENTITY_H
#define MYENTITY_H

#include <rt2d/entity.h>

/// @brief The MyEntity class is the Entity implementation.
class MyEntity : public Entity
{
public:
	/// @brief Constructor
	MyEntity();
	/// @brief Destructor
	virtual ~MyEntity();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	int x;
	int y;
	int totalwidth;
	int totalheight;

	Vector2 startPosition;


	

	Point2 deg1;
	Point2 deg2;
	Point2 deg3;
	Point2 deg4;
	Point2 deg5;
	Point2 deg6;
	Point2 deg7;
	Point2 deg8;
	Point2 deg9;
	Point2 deg10;
	Point2 deg11;
	Point2 deg12;

private:
	/* add your private declarations */
	
};

#endif /* MYENTITY_H */
