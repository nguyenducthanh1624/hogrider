#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
//#include "Map.h"


using namespace std;

bool checkCollision(SDL_Rect a, SDL_Rect b);

void makeSprites(SDL_Rect* rect, const int nFrames, int spriteW, int spriteH);

bool checkWall(vector<vector<int>>&map, SDL_Rect entity);
	

