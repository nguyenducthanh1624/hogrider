#include "Dot.h"




Dot::Dot(int x ,int y, int w ,int h) {
	mPosX = x;
	mPosY = y;

	mCollider.w = w;
	mCollider.h = h;

	mVelX = 0;
	mVelY = 0;

	mStatus = 0; // 0 means idle

}

void Dot::handleEvent(SDL_Event& e) {
	
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		
		mStatus = 1; // 1 means moving
		switch (e.key.keysym.sym) 
		{
		case SDLK_UP:
			mVelY -= DOT_VEL;
			break;
		case SDLK_DOWN:
			mVelY += DOT_VEL;
			break;
		case SDLK_RIGHT:
			mVelX += DOT_VEL;
			break;
		case SDLK_LEFT:
			mVelX -= DOT_VEL;
			break;

		case SDLK_SPACE:
			mStatus = 2;
			//mPosY -= JUMP_HEIGHT;
			//std::cout << mPosY << std::endl;
			
			break;
		}
		//std::cout << mVelX << std::endl;
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		//mStatus = 0;
		//std::cout << "ococc" << std::endl;
		switch (e.key.keysym.sym) 
		{
			
		case SDLK_UP: mVelY += DOT_VEL;mStatus = 0;break;
		case SDLK_DOWN: mVelY -= DOT_VEL;mStatus = 0; break;
		case SDLK_RIGHT:mVelX -= DOT_VEL;mStatus = 0;break;
		case SDLK_LEFT: mVelX += DOT_VEL;mStatus = 0;break;
		case SDLK_SPACE: mStatus=0;break;
		}
		
	}
	//std::cout << mStatus<< std::endl;
}

//this one also need modification
//it needds to know the width and height of the screen
void Dot::move(const int SCRW, const int SCRH,SDL_Rect& wall) {
	mPosX += mVelX;
	mCollider.x = mPosX;


	if ((mPosX < 0) || (mPosX + mCollider.w > SCRW) ||checkCollision(mCollider,wall))
	{
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}

	//mVelY += GRAVITY;
	mPosY += mVelY;
	
	
	mCollider.y = mPosY;
	if ((mPosY < 0) || (mPosY + mCollider.h > SCRH-100) || checkCollision(mCollider,wall)) {
		
		mPosY -= mVelY;
		mCollider.y = mPosY;
		
	}

	
}

//HOLY BALLS IT ACTUALLY WORKED
//THANK YOU RANDOM STRANGER ON REDDIT
void Dot::walk(const int SCRW, const int SCRH, SDL_Rect& wall,SDL_Rect entity, int x, int y) {
	if (mPosX != x-15 || mPosY != y) {
		
		//THE ENEMY NEEDS TO KNOW THE POSITION OF THE PLAYER SO IT CAN KINDA MAKE A VECTOR POINTING TORWARDS THE PLAYER
		//THEN IT NEEDS TO NORMALIZE THAT VECTOR SO IT CAN CONSTANTLY MOVE TORWARDS THE PLAYER

		//OK SO THE ENEMIES SOMETIMES LOOK LIKE THEY'RE PHASING OUT OF REALITY
		//GOTTA IMPROVE THAT WHOLE NORMALIZATION THING
		 mPosX += 3 * (x - mPosX) / sqrt((x - mPosX) * (x - mPosX) + (y - mPosY) * (y - mPosY));
		 mPosY += 3 *  (y - mPosY) / sqrt((x - mPosX) * (x - mPosX) + (y - mPosY) * (y - mPosY));
		
		//mVelX -= 10;
	}

	mCollider.x = mPosX;
	if (mPosX < 0 || (mPosX + mCollider.w > SCRW) || checkCollision(mCollider, entity)) {
		mPosX = x - 15;
		mCollider.x = mPosX;
	}

	mCollider.y = mPosY;
	if ((mPosY < 0) || (mPosY + mCollider.h > SCRH - 100) || checkCollision(mCollider, entity)) {

		//mPosY -= mVelY;
		mPosY = y;
		mCollider.y = mPosY;

	}
	
}

int Dot::getStatus() {
	return mStatus;
}


//gotta modify this as well
//because the render function of ltexture takes in the global renderer
//so now this one will have to do the same
//abt the global dot texture, we must pass by reference so the render func of the dot can fuck around with the dot texture
// and not just a copy of it


//ong ong it worked
//ok so we gotta add a flip to it to make the character face the right way when they move yknow
//that means I have to add flip to the render func in LTexture as well
void Dot::render(SDL_Renderer* gRen,LTexture &gDotTexture,SDL_Rect* clip,SDL_RendererFlip flip) {
	gDotTexture.render(gRen, mPosX, mPosY, clip,flip);
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