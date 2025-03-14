#include "Handler.h"

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;


	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	return true;
}

//holy shit I made this shit myself
//still bad for memory though

// cause yknow every texture sheet we load needs an array of rects(clips)

void makeSprites(SDL_Rect* rect, const int nFrames, int spriteW, int spriteH,int start) {
	
	for (int i = 0;i < nFrames;i++) {
		rect[i].w = spriteW;
		rect[i].h = spriteH;
		rect[i].x = spriteW * i + start;
		rect[i].y = 0;
	}
}