#include "LTexture.h"

LTexture::LTexture() {
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer) {
	free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;
	return mTexture != nullptr;
}

bool LTexture::loadFromRenderedText(SDL_Renderer* renderer,TTF_Font* font, std::string textureText, SDL_Color textColor) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

	mTexture = SDL_CreateTextureFromSurface( renderer, textSurface);

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

	return mTexture != nullptr;
}



void LTexture::free() {
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(SDL_Renderer* renderer ,int x, int y, SDL_Rect* clip,SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad,NULL,NULL,flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}