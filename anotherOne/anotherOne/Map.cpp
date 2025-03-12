#include "Map.h"


vector<vector<int>>lvl1 = {
	{1,1,1,1,1,1,1,1,1,0,0,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
};

Map::Map(SDL_Renderer* gRen) {
	SDL_Texture* tmpTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load("wall.png");

	tmpTexture = SDL_CreateTextureFromSurface(gRen, loadedSurface);

	wall = tmpTexture;

	SDL_FreeSurface(loadedSurface);

	LoadMap(lvl1);

	src.x = 0;
	src.y = 0;
	src.w = dest.w= 48;
	src.h = dest.h = 48;

	dest.x = dest.y = 0;

}

void Map::LoadMap(vector<vector<int>>&arr) {
	/*for (int row = 0;row < 10;row++) {
		for (int col = 0;col < 15;col++) {
			map[row][col] = arr[row][col];
		}
	}*/
	map = arr;
}

void Map::Draw(SDL_Renderer* gRen, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(gRen, tex, &src, &dest);

}



void Map::DrawMap(SDL_Renderer* gRen) {
	int type = 0;
	for (int row = 0;row < 10;row++) {
		for (int col = 0;col < 15;col++) {
			type = map[row][col];

			dest.x = col * 48;
			dest.y = row * 48;

			if (type == 1) {
				Draw(gRen, wall, src, dest);
			}
		}
	}
}

