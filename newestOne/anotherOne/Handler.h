#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>

bool checkCollision(SDL_Rect a, SDL_Rect b);


void makeSprites(SDL_Rect* rect,const int nFrames, int spriteW, int spriteH);
	

