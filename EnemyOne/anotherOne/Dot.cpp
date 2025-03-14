#include "Dot.h"




Dot::Dot() {
	mPosX = 0;
	mPosY = 0;

	mCollider.w = DOT_W;
	mCollider.h = DOT_H;

	mVelX = 0;
	mVelY = 0;

}

void Dot::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
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
			
			mPosY -= JUMP_HEIGHT;

			//mPosY += JUMP_HEIGHT;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) 
		{
		case SDLK_UP: mVelY += DOT_VEL;break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_RIGHT:mVelX -= DOT_VEL;break;
		case SDLK_LEFT: mVelX += DOT_VEL;break;
		case SDLK_SPACE: mPosY += JUMP_HEIGHT;break;
		}
	}
}

//this one also need modification
//it needds to know the width and height of the screen
void Dot::move(const int SCRW, const int SCRH,SDL_Rect& wall) {
	mPosX += mVelX;
	mCollider.x = mPosX;


	if ((mPosX < 0) || (mPosX + DOT_W > SCRW) ||checkCollision(mCollider,wall))
	{
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}
	mVelY += GRAVITY;
	mPosY += mVelY;
	
	
	mCollider.y = mPosY;
	if ((mPosY < 0) || (mPosY + DOT_H > SCRH-100) || checkCollision(mCollider,wall)) {
		
		mPosY -= mVelY;
		mCollider.y = mPosY;
		
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
void Dot::render(SDL_Renderer* gRen,LTexture &gDotTexture,SDL_Rect* clip,SDL_RendererFlip flip) {
	gDotTexture.render(gRen, mPosX, mPosY, clip,flip);
}

int Dot::getPosX() {
	return mPosX;
}

int Dot::getPosY() {
	return mPosY;
}