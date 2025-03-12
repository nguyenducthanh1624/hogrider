#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>



//the solution to any problem is just shoving the global renderer into it
//I should probably switch it's name to gRen though
class LTexture {
public:

	LTexture();
	~LTexture();

	//like this one
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//or this one
	bool loadFromRenderedText(SDL_Renderer* renderer,TTF_Font* font, std::string textureText, SDL_Color textColor);


	void free();

	//and this one

	//more modification
	//added flip so sprite clip can flip
	void render(SDL_Renderer* renderer,int x, int y, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
