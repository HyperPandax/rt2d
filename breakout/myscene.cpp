/**
 * This class describes MyScene behavior.
 *
 * Copyright 2018 Lisanne <lnreilman.nl>
 */

 // #include
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 
#include <ctime>

#include "myscene.h"
#include "block.h"
#include "star.h"


//======================================================================
//								Constructor							   |
//======================================================================
MyScene::MyScene() : Scene()
{	//------------------------------------------------------------------
	//						Start the timer.
	//------------------------------------------------------------------
	t.start();
	gameOver = false;

	//------------------------------------------------------------------
	//							Instances
	//------------------------------------------------------------------
	//paused text
	pausede = new Star();
	pausede->addSprite("assets/paused.tga");
	pausede->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	pausede->velocity = Vector2(0, 0);
	pausede->scale = Point(2.2f, 1.0f);

	//dead text
	dead = new Star();
	dead->addSprite("assets/ulost.tga");
	dead->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	dead->velocity = Vector2(0, 0);
	dead->scale = Point(2.2f, 1.0f);

	//won text
	won = new Star();
	won->addSprite("assets/uwon.tga");
	won->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	won->velocity = Vector2(0, 0);
	won->scale = Point(2.2f, 1.0f);

	//platform
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH / 2, 700);
	//TEST myentity->scale = Point2(10.0f, 0.2f);

	//mystar
	mystar = new Star();
	mystar->hearts = 4;
	
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

	//------------------------------------------------------------------
	//							Vectors
	//------------------------------------------------------------------
	//vector of blocks
	blocks = std::vector<Block*>();
	//vector of bonus
	bonuses = std::vector<Bonus*>();
	//vector of blockText
	blockNr = std::vector<Text*>();

	//------------------------------------------------------------------
	//							Functions
	//------------------------------------------------------------------
	spawnBlocks();
	giveBonus();

	//------------------------------------------------------------------
	//							Add childs
	//------------------------------------------------------------------
	this->addChild(star1);
	this->addChild(star2);
	this->addChild(star3);

	this->addChild(myentity);
	this->addChild(mystar);

	//------------------------------------------------------------------
	//							Overige vars
	//------------------------------------------------------------------
	this->toTurn = 0;
	this->paused = false;

	mystar2 = new Star();
	mystar2->hearts = 1;
	mystar2->velocity = Vector2(0, 0);
}

//======================================================================
//								Deconstructor						   |
//======================================================================
MyScene::~MyScene()
{
	// deconstruct and delete the Tree

	//forloop delete blocks
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
	//delete bonuses
	for (auto it = bonuses.begin(); it != bonuses.end();) {
		if ((*it)->toErase >= 1) {
			removeChild(*it);
			delete(*it);
			it = bonuses.erase(it);
		}
		else {
			++it;
		}

	}

	mystar->position = mystar->startPosition;

	this->removeChild(myentity);
	this->removeChild(mystar);
	this->removeChild(mystar2);
	this->removeChild(star1);
	this->removeChild(star2);
	this->removeChild(star3);
	

	// delete myentity & mystar from the heap (there was a 'new' in the constructor)
	delete myentity;
	delete mystar;
	delete mystar2;
	delete star1;
	delete star2;
	delete star3;

	delete won;
	delete dead;
	delete pausede;
}

//======================================================================
//								Update								   |
//======================================================================
void MyScene::update(float deltaTime)
{
	checkAmountBlocks();

	if (blocksSize <= 0) {
		this->addChild(won);
		this->paused = true;
		this->removeChild(mystar);
	}
	if (blocksSize >= 1 && gameOver == true) {
		this->addChild(dead);
		this->paused = true;
	}

	//if its crashed to outside go to startpos
	if (mystar->position.x > SWIDTH + 30 || mystar->position.x < -30 || mystar->position.y > SHEIGHT + 30 || mystar->position.y < -30) {
		mystar->position = mystar->startPosition;
	}

	//------------------------------------------------------------------
	//							ESC == Pauze
	//------------------------------------------------------------------
	if (input()->getKeyUp(KeyCode::Escape)) {
		if (!this->paused) {
			this->paused = true;
			this->addChild(pausede);
		}
		else {
			this->paused = false;
			this->removeChild(pausede);
		}
	}
	if (finishedD == true) {
		if (!this->paused) {
			this->paused = true;
			this->addChild(dead);
		}
		else {
			this->paused = false;
			this->removeChild(dead);
		}
	}
	if (this->paused) {
			return;
	}
	
	//------------------------------------------------------------------
	//					Rotation color star & platform
	//------------------------------------------------------------------
	
	if (t.seconds() > 0.0333f) {
		RGBAColor color = myentity->sprite()->color;
		myentity->sprite()->color = Color::rotate(color, 0.01f);
		RGBAColor color2 = mystar->sprite()->color;
		mystar->sprite()->color = Color::rotate(color2, 0.01f);
		
		t.start();
	}

	//------------------------------------------------------------------
	//						Movement platform
	//------------------------------------------------------------------
	
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
	
	//------------------------------------------------------------------
	//		Makes sure the platform doesn't get stuck on the sides
	//------------------------------------------------------------------
	
	if (myentity->position.x <= 64 ) {
		myentity->position.x += 10;
	}
	if (myentity->position.x >= 1216) {
		myentity->position.x -= 10;
	}

	//------------------------------------------------------------------
	//					Erase blocks who are hit
	//------------------------------------------------------------------
	erase();
	
	//------------------------------------------------------------------
	//					If star hits platform bounce
	//------------------------------------------------------------------
	
	if (AABC(this->mystar, this->myentity)) {

		// in progress
		int paddleX = this->myentity->position.x;
		int starX = this->mystar->position.x;

		int deg = paddleX - starX;
		std::cout << deg << std::endl;

	
		//
		//10 tot 170 graden
		//
		//
		//
		//
		//
		//

		//mystar->velocity.x += deg * -1;
		//mystar->velocity.y -= deg * -0.5;
		std::cout << mystar->velocity << std::endl;

		
		this->mystar->turny();
		mystar->position.y -= 10;
	}
	if (AABC(this->mystar2, this->myentity)) {
		this->mystar2->turny();
		mystar2->position.y -= 10;
	}

	//------------------------------------------------------------------
	//			If star hits block bounce and set block to erase
	//------------------------------------------------------------------
	
	for (int i = 0; i < blocks.size(); i++) {
		if (AABB(this->mystar, this->blocks[i])) {			
			b = blocks[i];
			b->toErase = 1;

			for (int c = 0; c < bonuses.size(); c++) {
				Bonus* bo = bonuses[c];
				if (b->num == bo->num) {
					addChild(bo);
					bo->velocity = Vector2(0, 100);

				}
			}
		}
		if (AABB(this->mystar2, this->blocks[i])) {
			b = blocks[i];
			b->toErase = 1;

			for (int c = 0; c < bonuses.size(); c++) {
				Bonus* bo = bonuses[c];
				if (b->num == bo->num) {
					addChild(bo);
					bo->velocity = Vector2(0, 100);
				}
			}
		}
	}

	//------------------------------------------------------------------
	//							turn the star
	//------------------------------------------------------------------
	
	if (this->toTurn == 2) {
		mystar->turny();
		toTurn = 0;
	}

	//------------------------------------------------------------------
	//					collision bonus platform
	//------------------------------------------------------------------
		
	for (int i = 0; i < bonuses.size(); i++) {
		if (AABD( this->bonuses[i], this->myentity)) {
			Bonus* meep = this->bonuses[i];
			if (meep->sprite()->color == RED) {
				if (mystar->hearts < 4)
				{
					mystar->hearts++;
				}
				
				std::cout << mystar->hearts << std::endl;
			}	
			if (meep->sprite()->color == ORANGE) {

				
				//this->myentity->scale = Vector2(2.2f, 0.2f);
				//timer
				ax.start();
			}
			if (meep->sprite()->color == YELLOW) {
				
				//this->addChild(mystar2);
				//timer
				bx.start();
			}
			if (meep->sprite()->color == GREEN) {
				mystar->velocity.x *= 2;
				mystar->velocity.y *= 2;
				//timer
				cx.start();
			}
			if (meep->sprite()->color == BLUE) {
				mystar->scale = Point(0.09f, 0.09f);
				//timer
				dx.start();
			}
			meep->toErase = 1;
		}
	}
	//timers bonus
	if (ax.seconds() > 5.0f) {	
		//this->myentity->scale = Vector2(1.6f, 0.2f);
		ax.stop();
	}
	if (bx.seconds() > 5.0f) {
		//this->removeChild(mystar2);
		mystar2->position = mystar2->startPosition;
		bx.stop();
	}
	if (cx.seconds() > 5.0f) {
		mystar->velocity.x /= 2;
		mystar->velocity.y /= 2;
		cx.stop();
	}
	if (dx.seconds() > 5.0f) {
		mystar->scale = Point(0.15f, 0.15f);
		dx.stop();
	}

	//------------------------------------------------------------------
	//					game paused when u die
	//------------------------------------------------------------------
	
	if (mystar->hearts <= 0) {
			mystar->velocity = Vector2(0, 0);
			this->removeChild(mystar);

			//GAME OVER	sprite
			gameOver = true;
			std::cout << "Game Over" << std::endl;
	}
	if (mystar->hearts <= 3) {
		//std::cout << "3 LIVES" << std::endl;
		this->removeChild(star3);
	}
	if (mystar->hearts <= 2) {
		//std::cout << "2 LIVES" << std::endl;
		this->removeChild(star2);
	}
	if (mystar->hearts <= 1) {
		//std::cout << "2 LIVES" << std::endl;
		this->removeChild(star1);
	}
	if (mystar->hearts >= 4) {
		this->addChild(star3);
	}
	if (mystar->hearts >= 3) {
		this->addChild(star2);
	}
	if (mystar->hearts >= 2) {
		this->addChild(star1);
	}
}

//======================================================================
//|								Functions							   |
//======================================================================

void MyScene::checkAmountBlocks() {
	blocksSize = this->blocks.size();
	//std::cout << /*"Amount Blocks: " +*/ blocksSize << std::endl;
}

void MyScene::spawnBlocks() {
	for (int i = 0; i <55; i++) {
		if (i <= 10) {
			Block* b = new Block();
			b->sprite()->color = RED;
			b->position = Point2(SWIDTH / 12 * (1 + i), SHEIGHT / 16 * 1);
			b->scale = Point(0.7f, 0.4f);
			this->addChild(b);
			blocks.push_back(b);

			/*int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message( s , RED);

			blockNr.push_back(numt);
			addChild(numt);*/

		}if (i <= 21 && i > 10) {
			Block* b = new Block();
			b->sprite()->color = ORANGE;
			b->position = Point2(SWIDTH / 12 * (1 + (i-11)), SHEIGHT / 16 * 2);
			b->scale = Point(0.7f, 0.4f);
			this->addChild(b);
			blocks.push_back(b);

			/*int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, ORANGE);

			blockNr.push_back(numt);
			addChild(numt);*/

		}if (i <= 32 && i > 21) {
			Block* b = new Block();
			b->sprite()->color = YELLOW;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 22)), SHEIGHT / 16 * 3);
			b->scale = Point(0.7f, 0.4f);
			this->addChild(b);
			blocks.push_back(b);

			/*int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, YELLOW);

			blockNr.push_back(numt);
			addChild(numt);*/

		}if (i <= 43 && i > 32) {
			Block* b = new Block();
			b->sprite()->color = GREEN;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 33)), SHEIGHT / 16 * 4);
			b->scale = Point(0.7f, 0.4f);
			this->addChild(b);
			blocks.push_back(b);

			/*int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, GREEN);

			blockNr.push_back(numt);
			addChild(numt);*/

		}if (i <= 55 && i > 43) {
			Block* b = new Block();
			b->sprite()->color = BLUE;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 44)), SHEIGHT / 16 * 5);
			b->scale = Point(0.7f, 0.4f);
			this->addChild(b);
			blocks.push_back(b);

			/*int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, BLUE);

			blockNr.push_back(numt);
			addChild(numt);*/
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

bool MyScene::AABD(Bonus* A, MyEntity* B) {
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
	//delete blocks
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
	//delete bonuses
	for (auto it = bonuses.begin(); it != bonuses.end();) {
		if ((*it)->toErase >= 1) {
			removeChild(*it);
			delete(*it);
			it = bonuses.erase(it);
		}
		else {
			++it;
		}

	}
}

void MyScene::giveBonus() {
	//gen random num between 0 and blocks.size
	
	std::srand((unsigned)time(nullptr));
	//TEST for (int i = 0; i < 1; i++) {
	for (int i = 0; i < 10; i++) {
		int size = blocks.size();
		int r = std::rand() % size; //TEST 45;   

		Bonus* bs = new Bonus();
		bs->position = blocks[r]->position;
		blocks[r]->num = r;
		bs->num = r;
		bonuses.push_back(bs);
		//TEST addChild(bs);

		int color = std::rand() % 5; //TEST 2;
		
		std::cout << color << std::endl;
		
		if (color == 0) {
			bs->sprite()->color = RED;  //TEST	GREEN
		}else if (color == 1) {
			bs->sprite()->color = ORANGE; //TEST	GREEN
		}else if (color == 2) {
			bs->sprite()->color = RED; //TEST	GREEN
		}else if (color == 3) {
			bs->sprite()->color = GREEN;
		}else if (color == 4) {
			bs->sprite()->color = BLUE; //TEST	GREEN
		}
		
		//if 2 nums the same

		std::cout <<"bs.num " << bs->num << " blocks[r].num "<< blocks[r]->num << std::endl;
	}
}