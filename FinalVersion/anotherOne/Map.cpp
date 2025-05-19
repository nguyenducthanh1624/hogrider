#include "Map.h"

Tile::Tile(int x, int y, int tileType)
{
	
	mBox.x = x;
	mBox.y = y;

	mBox.w = 48;
	mBox.h = 48;

	
	mType = tileType;
}


void Tile::render(SDL_Renderer* gRen, LTexture& gTileTex,SDL_Rect& sometile)
{
	gTileTex.render(gRen, mBox.x , mBox.y , &sometile);
	
}

int Tile::getType() {
	return mType;
}

SDL_Rect Tile::getBox() {
	return mBox;

}