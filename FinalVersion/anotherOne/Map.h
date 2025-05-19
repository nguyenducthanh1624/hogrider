#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"

class Tile
{
public:
	Tile(int x, int y, int tileType);
	void render(SDL_Renderer* gRen, LTexture& gTileTex, SDL_Rect& sometile);
	int getType();
	SDL_Rect getBox();

private:
	SDL_Rect mBox;

	int mType;
};