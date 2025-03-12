#pragma once

#include "LTexture.h"
#include <vector>
using namespace std;


class Map {
public:
	
	Map(SDL_Renderer* gRen);
	~Map();

	void LoadMap(vector<vector<int>>&arr);
	static void Draw(SDL_Renderer* gRen, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	void DrawMap(SDL_Renderer* gRen);

	

private:
	SDL_Rect src, dest;
	SDL_Texture* wall;
	vector<vector<int>> map;
	
};