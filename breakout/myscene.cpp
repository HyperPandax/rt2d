/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
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

	//------------------------------------------------------------------
	//							Instances
	//------------------------------------------------------------------
	//platform
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH / 2, 700);
	myentity->scale = Point(1.0f, 0.1f);

	//mystar
	mystar = new Star();
	mystar->hearts = 3;
	//mystar->velocity = Vector2(0, 0);
	std::cout << "hearts:" << mystar->hearts << std::endl;
	

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
}

//======================================================================
//								Deconstructor						   |
//======================================================================
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

//======================================================================
//								Update								   |
//======================================================================
void MyScene::update(float deltaTime)
{
	//bonusTimer++;
	bonusTimer += 1* deltaTime;
	std::cout << bonusTimer << std::endl;
	if (bb == 4 ) {
		bonusTimer = 0;
		if (bonusTimer >= 3.0f) {

			std::cout << "SCALEEEEE" << std::endl;
			mystar->scale = Point(0.15f, 0.15f);
			
		}
		bb = 0;
	}


	//------------------------------------------------------------------
	//							ESC == Pauze
	//------------------------------------------------------------------
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
		this->mystar->turny();
		mystar->position.y -= 10;
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
				if (mystar->hearts < 3)
				{
					mystar->hearts++;
				}
				
				std::cout << mystar->hearts << std::endl;
				bb = 0;
			}	
			if (meep->sprite()->color == ORANGE) {

				//timer
				this->myentity->scale = Vector2(2.0f, 0.1f);
				bb = 1;
			}
			if (meep->sprite()->color == YELLOW) {
				
				this->addChild(mystar2);
				bb = 2;
			}
			if (meep->sprite()->color == GREEN) {
				mystar->velocity.x *= 1.5;
				mystar->velocity.y *= 1.5;
				bb = 3;
			}
			if (meep->sprite()->color == BLUE) {
				mystar->scale = Point(0.09f, 0.09f);
				bb = 4;
			}
			meep->toErase = 1;
		}
	}

	//------------------------------------------------------------------
	//					game paused when u die
	//------------------------------------------------------------------
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
	if (mystar->hearts >= 3) {
		this->addChild(star3);
	}
	if (mystar->hearts >= 2) {
		this->addChild(star2);
	}
		/*if (mystar2->hearts == 0) {
			this->removeChild(mystar2);
		}*/


	//bonus shit timers enz

	/*if (bb ==1) {
		bonusTimer.start();
		if (bonusTimer.seconds() > 3.0f) {
			this->myentity->scale = Vector2(1.0f, 0.1f);
		}
		bonusTimer.stop();
	}
	if(bb == 2) {
		bonusTimer.start();
		if (bonusTimer.seconds() > 3.0f) {
			removeChild(mystar2);
		}
		bonusTimer.stop();
	}
	if (bb == 3) {
		bonusTimer.start();
		if (bonusTimer.seconds() > 3.0f) {
			
		}
		bonusTimer.stop();
	}
	if (bb == 4) {
		
		if (bonusTimer.seconds() > 3.0f) {
			this->mystar->scale = Point(0.15f, 0.15f);
		}
		//bonusTimer.stop();
		bonusTimer.start();
		bb = 0;
	}*/

	

}

//======================================================================
//|								Functions							   |
//======================================================================

void MyScene::spawnBlocks() {
	for (int i = 0; i <55; i++) {
		if (i <= 10) {
			Block* b = new Block();
			b->sprite()->color = RED;
			b->position = Point2(SWIDTH / 12 * (1 + i), SHEIGHT / 16 * 1);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);

			int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message( s , RED);

			blockNr.push_back(numt);
			addChild(numt);

		}if (i <= 21 && i > 10) {
			Block* b = new Block();
			b->sprite()->color = ORANGE;
			b->position = Point2(SWIDTH / 12 * (1 + (i-11)), SHEIGHT / 16 * 2);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);

			int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, ORANGE);

			blockNr.push_back(numt);
			addChild(numt);

		}if (i <= 32 && i > 21) {
			Block* b = new Block();
			b->sprite()->color = YELLOW;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 22)), SHEIGHT / 16 * 3);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);

			int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, YELLOW);

			blockNr.push_back(numt);
			addChild(numt);

		}if (i <= 43 && i > 32) {
			Block* b = new Block();
			b->sprite()->color = GREEN;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 33)), SHEIGHT / 16 * 4);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);

			int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, GREEN);

			blockNr.push_back(numt);
			addChild(numt);

		}if (i <= 55 && i > 43) {
			Block* b = new Block();
			b->sprite()->color = BLUE;
			b->position = Point2(SWIDTH / 12 * (1 + (i - 44)), SHEIGHT / 16 * 5);
			b->scale = Point(0.7f, 0.2f);
			this->addChild(b);
			blocks.push_back(b);

			int num = i;
			std::string s = std::to_string(num);
			Text* numt = new Text();
			numt->scale = Point2(0.35f, 0.35f);
			numt->position = Point2(b->position.x, b->position.y);
			numt->message(s, BLUE);

			blockNr.push_back(numt);
			addChild(numt);
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
	for (int i = 0; i < 1; i++) {
	//for (int i = 0; i < 10; i++) {
		int size = blocks.size();
		int r = 45; // std::rand() % size;

		

		Bonus* bs = new Bonus();
		bs->position = blocks[r]->position;
		blocks[r]->num = r;
		bs->num = r;
		bonuses.push_back(bs);
		addChild(bs);
		
		int color = 4; // std::rand() % 5;
		
		std::cout << color << std::endl;
		
		if (color == 0) {
			bs->sprite()->color = RED;
		}else if (color == 1) {
			bs->sprite()->color = ORANGE;
		}else if (color == 2) {
			bs->sprite()->color = YELLOW;
		}else if (color == 3) {
			bs->sprite()->color = GREEN;
		}else if (color == 4) {
			bs->sprite()->color = BLUE;
		}
		
		


		//if 2 nums the same

		std::cout <<"bs.num " << bs->num << " blocks[r].num "<< blocks[r]->num << std::endl;
	}


	/*std::srand((unsigned)time(nullptr));
	for (size_t i = 0; i < 9; i++) {
		int size = blocks.size();
		int r = std::rand() % size;
	
		blocks[r]->hasbonus = i;
		std::cout << "blocknr: " << r << " hasbonus: " << blocks[r]->hasbonus << " position: " <<blocks[r]->position << std::endl;

		Bonus* bs = new Bonus();
		bs->position = blocks[r]->position;
		bs->num = r;
		bonuses.push_back(bs);
		addChild(bs);

		std::cout << "num bonusz(r): " << bs->num << " position: " << bs->position << std::endl;
	}*/
		
	// choose bonus type

	// if bonus collides platform do bonus

	//if bonus hits platform
	//if (AABD())
}