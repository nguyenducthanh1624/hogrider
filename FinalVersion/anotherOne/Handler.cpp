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
		rect[i].x = start + spriteW * i;
		rect[i].y = 0;
	}
}


bool checkWall(SDL_Rect box, Tile* tiles[]) {
	for (int i = 0;i < 150;++i) {
		if (tiles[i]->getType() == 1) {
			if (checkCollision(box, tiles[i]->getBox())) {
				return true;
			}
		}
	}

	return false;
}

int randNumGen() {
	int min = 1;
	int max = 10000;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>distrib(min, max);

	int num = distrib(gen);
	return num;
}

void handlePlayButton(SDL_Event* e, LButton& playButton, bool& quitMenu, bool& play) {
	if (e->type == SDL_QUIT)
	{
		quitMenu = true;
	}

	if (playButton.handleEvent(e, 2))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			playButton.mCurrSprite = BUTTON_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			play = true;
			quitMenu = true;
			
			playButton.mCurrSprite = BUTTON_OVER;
			break;
		}
	}
	else
	{
		playButton.mCurrSprite = BUTTON_OUT;
	}
}


void handleExitButton(SDL_Event* e, LButton& exitButton, bool& Quit) {
	if (exitButton.handleEvent(e, 2))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			exitButton.mCurrSprite = BUTTON_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			exitButton.mCurrSprite = BUTTON_OVER;
			break;
		}
	}
	else
	{
		exitButton.mCurrSprite = BUTTON_OUT;
	}
}


void handleContinueButton(LButton& continueButton, LTexture& gContinueButtonTex, SDL_Event* e,
	SDL_Renderer* gRen,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State) {

	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (continueButton.handleEvent(e, 1))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					continueButton.mCurrSprite = BUTTON_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					continueButton.mCurrSprite = BUTTON_OVER;
					Game_State = true;
					Back_To_Game = true;
				}
				break;
				}
			}
			else
			{
				continueButton.mCurrSprite = BUTTON_OUT;
			}

			SDL_Rect* currentClip_Continue = &gContinueButton[continueButton.mCurrSprite];
			
			continueButton.render(gRen, currentClip_Continue, gContinueButtonTex);

			SDL_RenderPresent(gRen);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}


void handlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	LButton& pauseButton,
	LButton& continueButton,
	LTexture& gContinueButtonTexture,
	bool& Game_State) {

	if (pauseButton.handleEvent(e, 1))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			pauseButton.mCurrSprite = BUTTON_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			pauseButton.mCurrSprite = BUTTON_OVER;
			break;
		case SDL_MOUSEBUTTONUP:
			Game_State = false;
			handleContinueButton(continueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State);
			
			break;
		}
	}
	else
	{
		pauseButton.mCurrSprite = BUTTON_OUT;
	}
}


void DrawEndGameSelection(LTexture& gLoseTexture,
	SDL_Event* e,
	SDL_Renderer* gRen,
	bool& Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}
			}

			gLoseTexture.render(gRen,0,0);

			SDL_RenderPresent(gRen);
		}
	}

	
}


int makeRandomNum() {
	int min = 1;
	int max = 1000000;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>distrib(min, max);

	int num = distrib(gen);
	return num;
}

int printResult(int a, int b, int c) {
	int res;
	cout << a << " " << b << " " << c << endl;
	if (a == b && b == c) {
		res = 3;
		cout << "Congrats I guess \n";
	}
	else if (a == b || b == c || a == c) {
		res = 2;
		cout << "So close\n";
	}
	else {
		res = 0;
		cout << "Keep playing\n";
	}
	return res;
}

bool playMore(char x = 'y') {
	bool res=true;
	if (x == 'y') res = true;
	if (x == 'n') res = false;
	return res;
}


void printMessage(int x) {
	cout << "Did you know, 99.9";
	if (x > 20)x = 20;
	for (int i = 0;i < x;i++) {
		cout << '9';
	}
	cout << '%' << " of gamblers quit before they win BIG\n";
}


Uint32 callback(Uint32 interval, void* param)
{
	printf("Callback called back with message: %s\n", reinterpret_cast<char*>(param));

	return 0;
}

void handleGambling(int& score) {
	int arr[3];
	char x = 'y';
	int& money = score;
	int bets = 0;
	int count = 0;

	do {
		printMessage(count);
		//cout<<"Make your bets: ";
		do {
			cout << "Make your bets: ";
			cin >> bets;
			cout << endl;
		} while (bets <= 0);

		for (int i = 0;i < 3;i++) {
			arr[i] = makeRandomNum() % 6;
		}

		int profit = bets * printResult(arr[0], arr[1], arr[2]);
		money = money - bets + profit;
		cout << "Money: " << money << endl;

		cout << "Gamble more?\n";
		do {
			cin >> x;
		} while (x != 'y' && x != 'n');

		count++;
	} while (playMore(x) && money > 0);

	if (arr[0] == arr[1] && arr[1] == arr[2] && arr[0] != 0) money *= arr[0];
	cout << "\nFinal amount: " << money << endl;
	if (money == 0) cout << "Broke ass \n";
}


void writeHighScore(const char* file, int score) {
	auto present = std::chrono::system_clock::now();
	fstream out;
	out.open(file,ios::app); 
	if (!out) { 
		cerr << "file could not be opened\n" << endl;
		exit(1);
	}
	out << endl;
	out << score<<" "<<present<<" + 5";
	out.close();
}