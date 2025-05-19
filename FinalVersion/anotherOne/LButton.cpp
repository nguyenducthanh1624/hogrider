#include "LButton.h"


LButton::LButton() {
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrSprite = BUTTON_OUT;

}

LButton::LButton(int x, int y) {
	mPosition.x = x;
	mPosition.y = y;

	mCurrSprite = BUTTON_OUT;
}

void LButton::setPosition(int x, int y) {
	mPosition.x = x;
	mPosition.y = y;

}

bool LButton::handleEvent(SDL_Event* e, int size) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;

		int width;
		int height;


		if (size == 1) {
			width = 22;
			height = 34;

		}
		else {
			width = 150;
			height = 98;

		}


		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if (x < mPosition.x)
		{
			inside = false;
		}
		
		else if (x > mPosition.x + width)
		{
			inside = false;
		}
		
		else if (y < mPosition.y)
		{
			inside = false;
		}
		
		else if (y > mPosition.y + height)
		{
			inside = false;
		}
		return inside;

	}
	return false;
}

void LButton::render(SDL_Renderer* gRen, SDL_Rect* currClip, LTexture& gButtonTexture) {
	gButtonTexture.render(gRen, mPosition.x, mPosition.y, &currClip[mCurrSprite]);
}