#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <random>
#include "LTexture.h"
#include "Handler.h"
#include "Map.h"
#include "Timer.h"


//1st rule of fight club: do not create another object 
//only one object at a time

class Dot {
public:
	static const int DOT_W = 30;
	static const int DOT_H = 31;

	static const int DOT_VEL = 5;

	

	Dot(int x = 0, int y = 0, int w = 0, int h = 0,
		int health=100,double stamina=10,int damage=10000,int specialDam=0);

	~Dot();

	void handleEvent(SDL_Event &e);

	void move(const int SCRW,const int SCRH ,Tile* tiles[]);
	void walk(const int SCRW, const int SCRH, SDL_Rect entity, int x, int y,Tile* tiles[],Dot player);
	void hurt(SDL_Rect entity, Dot& enemy);
	void fight(int x, int y, Dot& player, Uint32 time);

	void reduceStamina(SDL_Event &e);

	void render(SDL_Renderer* gRen, LTexture& gDotTexture, SDL_Rect* clip, SDL_RendererFlip flip, int x = -100000);

	void knockBack(int x);

	void save(Dot& player);

	int getStatus();
	int getPosX();
	int getPosY();
	SDL_Rect getCollider();
	int mHealth;
	double mStamina;
	int mDamage;
	int mStatus;
	int mSpecialDam;
	
private:
	
	
	int mPosX, mPosY;
	int mVelX, mVelY;

	SDL_Rect mCollider;

};