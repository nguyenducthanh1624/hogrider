#pragma once

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>



class LTimer {
public:
	LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();


private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;


	bool mStarted;
	bool mPaused;

};