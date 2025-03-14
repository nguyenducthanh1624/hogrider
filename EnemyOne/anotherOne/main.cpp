#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "LTexture.h"
#include "LTimer.h"
#include "Dot.h"


const int SCRW = 640;
const int SCRH = 480;
const int SCR_FPS = 60;
const int SCR_TICKS_PER_FRAME = 1000 / SCR_FPS;

LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
LTexture gFPSTextTexture;
LTexture gDotTexture;
LTexture gDatTexture;



const int HOG_IDLE_FRAMES = 4;
const int HOG_MOVE_FRAMES = 8;
const int HOG_ATK_FRAMES = 5;





const int GOBLIN_FRAMES = 11;


SDL_Rect gHogIdleClips[HOG_IDLE_FRAMES];
SDL_Rect gHogMoveClips[HOG_MOVE_FRAMES];
SDL_Rect gHogAtkClips[HOG_ATK_FRAMES];

SDL_Rect gDatSprites[GOBLIN_FRAMES];
SDL_Window* gWin = nullptr;
SDL_Renderer* gRen= nullptr;
TTF_Font* gFont = NULL;



bool init();



bool loadMedia();


void close();

int main(int argc, char* args[]) {
	if (!init()) {
		printf("cant init\n");
	}
	else {
		if (!loadMedia()) {
			printf("cant load d=media\n");
		}
		else {
			bool quit = false;
			SDL_Event e;
			int startframe = 0;
			int datFrame = 0;

			SDL_Color textColor = { 0, 0, 0, 255 };

			Dot dot(10,10,30,31);
			Dot dat(300,300,12,15);

			SDL_Rect wall = { 300,40,40,400 };
			SDL_RendererFlip flipType = SDL_FLIP_NONE;
			SDL_RendererFlip facing = SDL_FLIP_NONE;
			
			

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT ) {
						flipType = SDL_FLIP_HORIZONTAL;
					}
					else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT ) {
						flipType = SDL_FLIP_NONE;
					}
					dot.handleEvent(e);
					
				}

				if (dat.getPosX() >= dot.getPosX()) {
					facing = SDL_FLIP_HORIZONTAL;
				}
				else {
					facing = SDL_FLIP_NONE;
				}
				dot.move(SCRW,SCRH,wall);
				dat.walk(SCRW, SCRH, wall, dot.getCollider(), dot.getPosX(), dot.getPosY());
				
				
				
				SDL_SetRenderDrawColor(gRen, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRen);

				
				SDL_Rect* DatClip = &gDatSprites[datFrame / GOBLIN_FRAMES];
				
				SDL_Rect* currentClip = &gHogIdleClips[startframe / 4];
				int lastFrame = HOG_IDLE_FRAMES;
				switch (dot.getStatus()) {
				case 0:
					currentClip = &gHogIdleClips[startframe / 5];
					lastFrame = HOG_IDLE_FRAMES;
					break;
				case 1:
					currentClip = &gHogMoveClips[startframe / 4];
					lastFrame = HOG_MOVE_FRAMES;
					break;
				case 2:
					currentClip = &gHogAtkClips[startframe / 4];
					lastFrame = HOG_ATK_FRAMES;
					break;
				}



				SDL_SetRenderDrawColor(gRen, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRen, &wall);

				dot.render(gRen,gDotTexture,currentClip,flipType);
				dat.render(gRen, gDatTexture, DatClip,facing);

				SDL_RenderPresent(gRen);

				++startframe;
				++datFrame;
				
				
				
				if (startframe / 4 >= lastFrame) startframe = 0;

				if (datFrame / GOBLIN_FRAMES>= GOBLIN_FRAMES) datFrame = 0;

			}
		}
	}

	close();
	return 0;
}



bool init() {
	bool success = true;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWin = SDL_CreateWindow("CHUD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);
	gRen = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(gRen, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;

	IMG_Init(imgFlags)& imgFlags;

	TTF_Init();

	return success;
}


bool loadMedia() {
	bool success = true;
	gFont = TTF_OpenFont("clash.ttf", 25);
	

	if (!gDotTexture.loadFromFile("cogrider.png",gRen)) {
		printf("wtffffffff\n");
		success = false;
	}

	if (!gDatTexture.loadFromFile("goblin.png", gRen)) {
		printf("ffftftftf\n");
	}

	//makeSprites(gSpriteClips, HOG_FRAMES, 30, 31);
	//makeSprites(gSpi)
	makeSprites(gHogIdleClips, 4, 30, 31);
	makeSprites(gHogMoveClips, 8, 30, 31, 120);
	makeSprites(gHogAtkClips, 5, 30, 31, 360);
	makeSprites(gDatSprites, GOBLIN_FRAMES, 12, 15);

	return success;
}


void close()
{
	//Free loaded images
	gTimeTextTexture.free();
	gPromptTextTexture.free();

	gFPSTextTexture.free();


	gDotTexture.free();
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRen);
	SDL_DestroyWindow(gWin);
	gWin = NULL;
	gRen = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}