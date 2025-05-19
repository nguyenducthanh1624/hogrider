#include "Dot.h"



Dot::Dot(int x, int y, int w, int h,int health,double stamina,int damage,int specialDam) {
	mHealth = health;
	mStamina = stamina;
	mDamage = damage;
	mSpecialDam = specialDam;
	mPosX = x;
	mPosY = y;

	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = w;
	mCollider.h = h;

	mVelX = 0;
	mVelY = 0;

	mStatus = 2; // 0 means idle
	
}

Dot::~Dot() {
	mPosX = -100;
	mPosY = -100;

	mCollider.x = 0;
	mCollider.y = 0;
	mCollider.w = 0;
	mCollider.h = 0;
}

void Dot::handleEvent(SDL_Event& e) {

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {

		mStatus = 1; // 1 means moving
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			mVelY -= DOT_VEL;
			break;
		case SDLK_s:
			mVelY += DOT_VEL;
			break;
		case SDLK_d:
			mVelX += DOT_VEL;
			break;
		case SDLK_a:
			mVelX -= DOT_VEL;
			break;

		/*case SDLK_SPACE:
			if(mStamina > 0) {
				mStatus = 2;
				mStamina-=1;
			}
			//else mStatus = 0;
			break;*/
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		//mStatus = 0;
		//std::cout << "ococc" << std::endl;
		switch (e.key.keysym.sym)
		{

		case SDLK_w: mVelY += DOT_VEL;mStatus = 0;break;
		case SDLK_s: mVelY -= DOT_VEL;mStatus = 0; break;
		case SDLK_d:mVelX -= DOT_VEL;mStatus = 0;break;
		case SDLK_a: mVelX += DOT_VEL;mStatus = 0;break;
		//case SDLK_SPACE: mStatus = 0;break;
		}

	}

	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (mStamina > 0) {
			mStatus = 2;
			//mStamina -= 1;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		mStatus = 0;
	}
	//std::cout << mStatus<< std::endl;
}

//this one also need modification
//it needds to know the width and height of the screen
void Dot::move(const int SCRW, const int SCRH,Tile* tiles[]) {
	mPosX += mVelX;
	mCollider.x = mPosX;


	if ((mPosX < 0) || (mPosX + DOT_W > SCRW) ||   checkWall(mCollider,tiles))
	{
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}

	mPosY += mVelY;
	mCollider.y = mPosY;
	if ((mPosY < 0) || (mPosY + DOT_H > SCRH) ||  checkWall(mCollider, tiles) ) {
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}


//this one kills the enemy
void Dot::walk(const int SCRW, const int SCRH, SDL_Rect entity, int x, int y,Tile* tiles[],Dot player) {
	if (!checkCollision(mCollider, entity)) {

		//THE ENEMY NEEDS TO KNOW THE POSITION OF THE PLAYER 
		//SO IT CAN KINDA MAKE A VECTOR POINTING TORWARDS THE PLAYER
		//THEN IT NEEDS TO NORMALIZE THAT VECTOR SO IT CAN CONSTANTLY MOVE TORWARDS THE PLAYER

		//OK SO THE ENEMIES SOMETIMES LOOK LIKE THEY'RE PHASING OUT OF REALITY
		//GOTTA IMPROVE THAT WHOLE NORMALIZATION THING

		//THERE I FIXED IT, IT'S NOT GLITCHING ANYMORE

		//OK SO I SHOULD USE THE HITBOXES INSTEAD OF THE X AND Y

		//LOOKS LIKE I STILL NEED VELOCITY
		mStatus = 1;
		int tmp = sqrt((x - mPosX) * (x - mPosX) + (y - mPosY) * (y - mPosY));
		mVelX = 3 * (x - mPosX) / tmp;
		mVelY = 3 * (y - mPosY) / tmp;

		mPosX += mVelX;
		mPosY += mVelY;

		mCollider.x = mPosX;
		mCollider.y = mPosY;

		

	}

	
	if ((mPosX < 0) || checkWall(mCollider, tiles))
	{
		
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}

	if ((mPosY < 0) ||  checkWall(mCollider, tiles)) {
		
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}

	if (checkCollision(mCollider, entity) && player.getStatus()==2) {
		//mStatus = 2;
		mHealth-=player.mDamage;
	}
	if (checkCollision(mCollider, entity) && mHealth>0) {
		mStatus = 2;
	}

	
	
}

//this is for the player
void Dot::hurt(SDL_Rect entity, Dot& enemy) {
	if (checkCollision(mCollider, entity) && enemy.mHealth > 0 && enemy.mStatus > 1) {
		mHealth-=enemy.mDamage;
		if (enemy.mStatus == 3) {
			mHealth -= enemy.mSpecialDam;
		}
	}
}

void Dot::fight(int x,int y,Dot& player,Uint32 time) {
	
	/*int min = 1;
	int max = 1000000;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>distrib(min, max);

	int num = distrib(gen);*/
	int dist = sqrt((x - mPosX) * (x - mPosX) + (y - mPosY) * (y - mPosY));

	
	//int dist = abs(x - mPosX);
	//std::cout << dist << std::endl;
	if (dist > 200) {
		mStatus = 0; 
	}
	else if (dist > 150 && dist < 200 && time % 5 == 0) {

		
		//SDL_TimerID timerID = SDL_AddTimer(3 * 1000, callback, (void*)"3 seconds waited!");

		mStatus = 2;
		
		
	}
	else if(dist<150 && checkCollision(mCollider, player.getCollider()) && time % 10 ==0) {
		//cout << "dist " <<dist<< endl;
		
		//SDL_TimerID timerID = SDL_AddTimer(3 * 1000, callback, (void*)"3 seconds waited!");
		mStatus = 3;
			
		player.knockBack(mPosX);
		

		

	}
	//cout << "dist " << dist << endl;
	if (checkCollision(mCollider, player.getCollider()) && player.getStatus() == 2) {
		//mStatus = 2;
		mHealth -= player.mDamage;
	}
	
	if (mHealth < 90000) {
		mDamage = 50;
		mSpecialDam = 250;
		int tmpX = 300;
		int tmpY = 300;
		mPosX = tmpX;
		mPosY = tmpY;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
	}

	if (mHealth < 50000) {
		mDamage = 60;
		mSpecialDam = 300;
		int tmpX = 200;
		int tmpY = 300;
		mPosX = tmpX;
		mPosY = tmpY;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
	}

	if (mHealth < 30000) {
		mDamage = 80;
		mSpecialDam = 350;
		int tmpX = 300;
		int tmpY = 150;
		mPosX = tmpX;
		mPosY = tmpY;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
	}

	if (mHealth < 10000) {
		mDamage = 50;
		mSpecialDam = 250;
		int tmpX = 150;
		int tmpY = 150;
		mPosX = tmpX;
		mPosY = tmpY;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
	}

	
}


void Dot::knockBack(int x) {
	mCollider.x = mPosX;

	if (mPosX >= x) {
		mPosX += 150;
		mCollider.x = mPosX;
	}
	else {
		mPosX -= 150;
		mCollider.x = mPosX;
	}

	mCollider.x = mPosX;
	
	//cout << mPosX << endl;
}


void Dot::save(Dot& player) {
	if (checkCollision(mCollider, player.getCollider())) {
		player.mHealth += 1000;
		mPosX = -100;
		mPosY = -100;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
		mCollider.w = 0;
		mCollider.h = 0;
		
	}
}

void Dot::reduceStamina(SDL_Event &e) {
	if (e.type == SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEBUTTONUP) {
		if (mStamina > 0) {
			//mStatus = 2;
			mStamina -= 2;
		}
	}
	
}

//gotta modify this as well
//because the render function of ltexture takes in the global renderer
//so now this one will have to do the same
//abt the global dot texture, we must pass by reference so the render func of the dot can fuck around with the dot texture
// and not just a copy of it


//ong ong it worked
//ok so we gotta add a flip to it to make the character face the right way when they move yknow
//that means I have to add flip to the render func in LTexture as well
void Dot::render(SDL_Renderer* gRen, LTexture& gDotTexture, SDL_Rect* clip, SDL_RendererFlip flip, int x) {

	if (x != -100000) {
		if (x < mPosX) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		else {
			flip = SDL_FLIP_NONE;
		}
	}
	gDotTexture.render(gRen, mPosX, mPosY, clip, flip);
}

int Dot::getStatus() {
	return mStatus;
}

int Dot::getPosX() {
	return mPosX;
}

int Dot::getPosY() {
	return mPosY;
}

SDL_Rect Dot::getCollider() {
	return mCollider;
}