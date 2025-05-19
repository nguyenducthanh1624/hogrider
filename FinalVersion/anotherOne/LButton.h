#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"

enum LButtonSprite {
	BUTTON_OUT = 0,
	BUTTON_OVER = 1,
	BUTTON_TOTAL = 2

};


class LButton {
public:
	LButton();

	LButton(int x, int y);

	void setPosition(int x, int y);

	bool handleEvent(SDL_Event* e,int size);

	void render(SDL_Renderer* gRen, SDL_Rect* currClip, LTexture& gButtonTexture);

	LButtonSprite mCurrSprite;
	//int mCurrSprite;
private:
	SDL_Point mPosition;

};


