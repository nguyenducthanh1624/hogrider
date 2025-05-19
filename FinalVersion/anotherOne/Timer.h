#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>


class LTimer
{
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

	bool mPaused;
	bool mStarted;
};