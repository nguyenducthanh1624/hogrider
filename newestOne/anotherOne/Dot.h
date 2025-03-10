#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Handler.h"

//1st rule of fight club: do not create another object 
//only one object at a time

class Dot {
public:
	static const int DOT_W = 20;
	static const int DOT_H = 20;

	static const int DOT_VEL = 5;
	static const int JUMP_HEIGHT = 30;
	static const int GRAVITY = 5;

	Dot();

	
	void handleEvent(SDL_Event &e);

	void move(const int SCRW,const int SCRH ,SDL_Rect& wall);

	void render(SDL_Renderer* gRen,LTexture &gDotTexture,SDL_Rect* clip,SDL_RendererFlip flip);


	int getPosX();
	int getPosY();

	int getStatus();

	
private:
	int mPosX, mPosY;

	int mVelX, mVelY;
	
	int mStatus;
	

	SDL_Rect mCollider;

};