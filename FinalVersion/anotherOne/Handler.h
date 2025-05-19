#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <ctime>
#include <chrono>
#include "Map.h"
#include "Dot.h"
#include "LButton.h"



using namespace std;

bool checkCollision(SDL_Rect a, SDL_Rect b);

void makeSprites(SDL_Rect* rect, const int nFrames, int spriteW, int spriteH,int start = 0);

bool checkWall(SDL_Rect box, Tile* tiles[]);

int randNumGen();

void handlePlayButton(SDL_Event* e, LButton& playButton, bool& quitMenu, bool& play);

void handleExitButton(SDL_Event* e, LButton& exitButton, bool& Quit);

void handleContinueButton(LButton& continueButton, LTexture& gContinueButtonTexture, SDL_Event* e,
	SDL_Renderer* gRen,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State);

void handlePauseButton(SDL_Event* e,
	SDL_Renderer* gRen,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	LButton& PauseButton,
	LButton& ContinueButton,
	LTexture& gContinueButtonTex,
	bool& Game_State);

void DrawEndGameSelection(LTexture& gLoseTex,
	SDL_Event* e,
	SDL_Renderer* gRen,
	bool& Play_Again);

int makeRandomNum();
int printResult(int a, int b, int c);
bool playMore(char x);
void printMessage(int x);


Uint32 callback(Uint32 interval, void* param);

void handleGambling(int& score);

void writeHighScore(const char* file, int score);