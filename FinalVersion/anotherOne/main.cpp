#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "LTexture.h"
#include "Dot.h"
#include "LButton.h"
#include "Timer.h"



const int SCRW = 720;
const int SCRH = 480;
const int SCR_FPS = 60;
const int SCR_TICKS_PER_FRAME = 1000 / SCR_FPS;


LTexture gHogTexture;//1
LTexture gValTexture;//2
LTexture gKnightTexture; //3
LTexture gPlayerTexture;

LTexture gDatTexture;
LTexture gPekTexture;

LTexture gBossTex;
LTexture gBossIdleTex;
LTexture gBossAtk1Tex;
LTexture gBossAtk2Tex;
LTexture gBossFlyTex;

LTexture gPlayButtonTex;
LTexture gExitButtonTex;
LTexture gBackButtonTex;
LTexture gPauseButtonTex;
LTexture gContButtonTex;
LTexture gMenuTex;
LTexture gWinTex;
LTexture gLoseTex;
LTexture gPauseTex;

LTexture playAgainTex;

LTexture gLaserTex;

LTexture gTileTex;
LTexture gPortalTex;

LTexture gHeartTex;

LTexture gTextTex;

LButton playButton(285, 180);
LButton exitButton(285,280+80);
LButton backButton(10, 10);
LButton pauseButton(10, 10);
LButton contButton(10, 10);


const int HOG_IDLE_FRAMES = 4;
const int HOG_MOVE_FRAMES = 8;
const int HOG_ATK_FRAMES = 5;
const int HOG_W = 30;
const int HOG_H = 31;
const int HOG_STAMINA = 10;

const int VAL_IDLE_FRAMES = 2;
const int VAL_MOVE_FRAMES = 3;
const int VAL_ATK_FRAMES = 4;
const int VAL_W = 31;
const int VAL_H = 18;
const int VAL_STAMINA = 20;

const int KNIGHT_IDLE_FRAMES = 2;
const int KNIGHT_MOVE_FRAMES = 4;
const int KNIGHT_ATK_FRAMES = 5;
const int KNIGHT_W = 26;
const int KNIGHT_H = 24;
const int KNIGHT_STAMINA = 20;

const int GOBLIN_IDLE_FRAMES = 3;
const int GOBLIN_MOVE_FRAMES = 3;
const int GOBLIN_ATK_FRAMES = 5;
const int GOBLIN_W = 12;
const int GOBLIN_H = 15;

const int GOBLIN_NUMBER = 100;
const int GOBLIN_FRAMES = 11;


const int PEKA_NUMBER = 100;
const int PEKA_FRAMES = 5;
const int PEKA_HP = 200;

const int ATK1_FRAMES = 9;
const int ATK2_FRAMES = 7;
const int IDLE_FRAMES = 15;
const int FLY_FRAMES = 6;


const int LASER_FRAMES = 16;
const int PORTAL_FRAMES = 8;

SDL_Rect gHogIdleClips[HOG_IDLE_FRAMES];
SDL_Rect gHogMoveClips[HOG_MOVE_FRAMES];
SDL_Rect gHogAtkClips[HOG_ATK_FRAMES];
SDL_Rect hogHP;

SDL_Rect gValIdleClips[VAL_IDLE_FRAMES];
SDL_Rect gValMoveClips[VAL_MOVE_FRAMES];
SDL_Rect gValAtkClips[VAL_ATK_FRAMES];
SDL_Rect valHP;

SDL_Rect gKnightIdleClips[KNIGHT_IDLE_FRAMES];
SDL_Rect gKnightMoveClips[KNIGHT_MOVE_FRAMES];
SDL_Rect gKnightAtkClips[KNIGHT_ATK_FRAMES];

SDL_Rect gTile[2];

SDL_Rect gDatSprites[GOBLIN_FRAMES];
SDL_Rect gPekSprites[PEKA_FRAMES];

SDL_Rect gBossIdleSprites[IDLE_FRAMES];
SDL_Rect gBossAtk1Sprites[ATK1_FRAMES];
SDL_Rect gBossAtk2Sprites[ATK2_FRAMES];
SDL_Rect gBossFlySprites[FLY_FRAMES];

SDL_Rect gLaserSprites[LASER_FRAMES];
SDL_Rect gPortalSprites[PORTAL_FRAMES];

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];

int DEATH[3] = { 15,30,1 };
//int DEATH[3] = { 1,1,0 };

SDL_Window* gWin = nullptr;
SDL_Renderer* gRen= nullptr;
TTF_Font* gFont = NULL;


bool setTiles(Tile* tiles[],string mapName) {
	bool tilesLoaded = true;
	int x = 0;
	int y = 0;
	std::ifstream map(mapName);

	for (int i = 0;i < 150;++i) {
		int tileType = 0;
		map >> tileType;

		if ((tileType >= 0) && (tileType < 2)) {
			tiles[i] = new Tile(x, y, tileType);

		}

		x += 48;

		if (x >= 720) {
			x = 0;
			y += 48;
		}
	}

	if (tilesLoaded) {
		gTile[1].x = 0;
		gTile[1].y = 0;
		gTile[1].w = 48;
		gTile[1].h = 48;

	}

	map.close();
	return tilesLoaded;
}


bool init();

bool loadMedia(Tile* tiles[]);

void close();

int main(int argc, char* args[]) {
	if (!init()) {
		printf("cant init\n");
	}
	else {
		Tile* tileset[150];
		if (!loadMedia(tileset)) {
			printf("cant load d=media\n");
		}
		else {
			

			/**/

			bool quitMenu = false;
			bool playAgain = false;
			

			while (!quitMenu) {
				
				SDL_Event eMouse;
				
				while (SDL_PollEvent(&eMouse) != 0) {
					
					
					if (eMouse.type == SDL_QUIT) {
						quitMenu = true;
					}

					bool quitGame = false;

					handlePlayButton(&eMouse, playButton, quitMenu, playAgain);
					handleExitButton(&eMouse, exitButton, quitMenu);

					if (quitGame==true) {
						return 0;
					}
					//cout << playButton.mCurrSprite << " " << exitButton.mCurrSprite << endl;
				}
				
				
				gMenuTex.render(gRen, 0, 0);

				playButton.render(gRen, gPlayButton, gPlayButtonTex);

				exitButton.render(gRen, gExitButton, gExitButtonTex);

				SDL_RenderPresent(gRen);
				
			}

			while (playAgain) {

				int startframe = 0;
				int datFrame = 0;
				int pekFrame = 0;

				int idleFrame = 0;
				int atk1Frame = 0;
				int atk2Frame = 0;
				int flyFrame = 0;

				int bossStartFrame = 0;

				int portalFrame = 0;

				int laserFrame = 0;
				int level = 0;
				int currDeathes = DEATH[0];

				int score = 0;
				int playerHP = 1000;
				
				SDL_Color textColor = { 0, 0, 0, 255 };

				Dot hog(50, 50, 30, 31, 1500, HOG_STAMINA, 50);
				Dot val(50, 50, 30, 31, 1000, VAL_STAMINA, 20);
				Dot knight(50, 50, 30, 31, 1200, KNIGHT_STAMINA, 30);
				Dot* player = &hog;
				Dot enemie;
				Dot* dats[GOBLIN_NUMBER];
				Dot* peks[PEKA_NUMBER];
				Dot boss(100, 100, 192, 112, 100000,10,20,200);
				Dot laser(-100, -100, 160, 960);
				Dot* hearts[5];
				string levels[3] = { "level1.map","level2.map","final.map" };


				for (int i = 0;i < GOBLIN_NUMBER;i++) {
					dats[i] = new Dot(150 * i, 100 * i, 12, 15, 100, 10, 5);
				}


				for (int i = 0;i < PEKA_NUMBER;i++) {
					peks[i] = new Dot(150 * i, 100 * i, 27, 21, 300, 10, 20);
				}

				int chance = randNumGen() % 6;
				//int chance = 0;
				if (chance == 0) {
					for (int i = 0;i < 5;i++) {
						hearts[i] = new Dot(randNumGen() % SCRW, randNumGen() % SCRH, 20, 20);
					}
				}


				


				SDL_RendererFlip flipType = SDL_FLIP_NONE;
				SDL_RendererFlip facing = SDL_FLIP_NONE;
				long long charSelect = 0;
				int deathes = 0;



				SDL_Event e;
				bool gameState = true;
				bool quit = false;
				LTimer stopTimer;
				stopTimer.start();
				
				setTiles(tileset, levels[level]);
				while (!quit) {
					//SDL_Event e;
					//checker cout << score << endl;

					//cout << level << endl;
					//stopTimer.start();
					// 
					int tmp = stopTimer.getTicks() / 1000.f;
					//cout << tmp << endl;
					while (SDL_PollEvent(&e) != 0) {

						
						//cout << hog.mHealth << " " << val.mHealth << " " << knight.mHealth << endl;
						//cout << hog.mStamina << " " << val.mStamina << " " << knight.mStamina << endl;
						//cout << hog.getPosX() << " "<<val.getPosX()<<" "<<knight.getPosX()<<" "<<player.getPosX()<<endl;
						if (hog.mHealth <= 0 && val.mHealth <= 0 && knight.mHealth <= 0) {
							quit = true;
							//playAgain = false;
						}

					
						if (e.type == SDL_QUIT) {
							quit = true;
							playAgain = false;
						}
						else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a) {
							flipType = SDL_FLIP_HORIZONTAL;

						}
						else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d) {
							flipType = SDL_FLIP_NONE;
						}

						else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e) {
							charSelect++;
							//std::cout << charSelect % 3 << std::endl;
						}
						handlePauseButton(&e, gRen, gContinueButton, pauseButton, contButton, gContButtonTex, gameState);
						
						hog.handleEvent(e);
						val.handleEvent(e);
						knight.handleEvent(e);
						//player.handleEvent(e);

						switch (charSelect % 3) {
						case 0:
							hog.reduceStamina(e);
							break;
						case 1:
							val.reduceStamina(e);
							break;
						case 2:
							knight.reduceStamina(e);
							break;
						}

					}

					//stopTimer.start();

					/*if (stopTimer.getTicks() / 1000.f >= 5) {
						//stopTimer.stop();
						cout << stopTimer.getTicks() / 1000.f << endl;
					}*/
					//cout << stopTimer.getTicks() / 1000.f << endl;

					switch (level) {
					case 0:
						
						deathes = 0;
						for (int i = 0;i < GOBLIN_NUMBER;i++) {
							if (dats[i]->mHealth > 0)dats[i]->walk(SCRW, SCRH, player->getCollider(), player->getPosX(), player->getPosY(), tileset, *player);
							else deathes++;
							/*switch (charSelect % 3) {
							case 0:
								hog.hurt(dats[i]->getCollider(), *dats[i]);
								break;
							case 1:
								val.hurt(dats[i]->getCollider(), *dats[i]);
								break;
							case 2:
								knight.hurt(dats[i]->getCollider(), *dats[i]);
								break;

							}*/
							player->hurt(dats[i]->getCollider(), *dats[i]);
						}
						break;
					case 1:
						
						deathes = 0;
						for (int i = 0;i < PEKA_NUMBER;i++) {
							if (peks[i]->mHealth > 0)peks[i]->walk(SCRW, SCRH, player->getCollider(), player->getPosX(), player->getPosY(), tileset, *player);
							else deathes++;
							player->hurt(peks[i]->getCollider(), *peks[i]);
							/*switch (charSelect % 3) {
							case 0:
								hog.hurt(peks[i]->getCollider(), *peks[i]);
								break;
							case 1:
								val.hurt(peks[i]->getCollider(), *peks[i]);
								break;
							case 2:
								knight.hurt(peks[i]->getCollider(), *peks[i]);
								break;
							}*/
						}
						break;
					case 2:
						
						deathes = 0;
						player->hurt(boss.getCollider(), boss);
						
						boss.fight(player->getPosX(), player->getPosY(), *player,tmp);
						boss.fight(hog.getPosX(), hog.getPosY(), hog,tmp);
						boss.fight(val.getPosX(), val.getPosY(), val,tmp);
						boss.fight(knight.getPosX(), knight.getPosY(), knight,tmp);
						break;

					}
					

					hog.move(SCRW, SCRH, tileset);
					val.move(SCRW, SCRH, tileset);
					knight.move(SCRW, SCRH, tileset);
					//player.move(SCRW, SCRH, tileset);

					SDL_SetRenderDrawColor(gRen, 108, 122, 137, 1);
					SDL_RenderClear(gRen);

					SDL_Rect* datClip = &gDatSprites[datFrame / GOBLIN_FRAMES];
					SDL_Rect* pekClip = &gPekSprites[pekFrame / PEKA_FRAMES];

					SDL_Rect* bossCurrClip = &gBossIdleSprites[bossStartFrame / IDLE_FRAMES];

					SDL_Rect* portalClip = &gPortalSprites[portalFrame / PORTAL_FRAMES];
					SDL_Rect* currentClip = &gHogIdleClips[startframe / 5];

					SDL_Rect* currLaserClip = &gLaserSprites[laserFrame / 1];
					SDL_Rect p{ 1000,1000,32,32 };

					SDL_Rect HP = { -100,-100,5,5 };


					int lastFrame = HOG_IDLE_FRAMES;
					int lastBossFrame = IDLE_FRAMES;
					if (player->mHealth <= 0)charSelect++;
					//if (player.mStamina < 10)player.mStamina += 0.5;
					switch (charSelect % 3) {
					case 0:
						player = &hog;
						playerHP = 1500;
						gPlayerTexture = gHogTexture;
						if (hog.mStamina < HOG_STAMINA)hog.mStamina+=0.1;
						switch (player->getStatus()) {
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
						break;
					case 1:

						player = &val;
						playerHP = 1000;
						gPlayerTexture = gValTexture;
						if (val.mStamina < VAL_STAMINA)val.mStamina+=0.1;
						switch (player->getStatus()) {
						case 0:
							currentClip = &gValIdleClips[startframe / 5];
							lastFrame = VAL_IDLE_FRAMES;
							break;
						case 1:
							currentClip = &gValMoveClips[startframe / 4];
							lastFrame = VAL_MOVE_FRAMES;
							break;
						case 2:
							

							currentClip = &gValAtkClips[startframe / 4];
							lastFrame = VAL_ATK_FRAMES;
							break;
						}
						break;
					case 2:
						player = &knight;
						playerHP = 1200;
						gPlayerTexture = gKnightTexture;
						if (knight.mStamina < KNIGHT_STAMINA)knight.mStamina+=0.1;
						switch (player->getStatus()) {
						case 0:
							currentClip = &gKnightIdleClips[startframe / 5];
							lastFrame = KNIGHT_IDLE_FRAMES;
							break;
						case 1:
							currentClip = &gKnightMoveClips[startframe / 4];
							lastFrame = KNIGHT_MOVE_FRAMES;
							break;
						case 2:

							currentClip = &gKnightAtkClips[startframe / 4];
							lastFrame = KNIGHT_ATK_FRAMES;
							break;
						}
						break;

					}
					pauseButton.render(gRen, gPauseButton, gPauseButtonTex);
					//player.reduceStamina(e);
					//if (player.mStamina < 10)player.mStamina += 1;

					//1st
					//if (player.mHealth > 0)player.render(gRen, gPlayerTexture, currentClip, flipType);

					switch (level) {
					case 0:
						for (int i = 0;i < GOBLIN_NUMBER;i++) {
							if (dats[i]->mHealth > 0) {
								dats[i]->render(gRen, gDatTexture, datClip, facing, player->getPosX());
							}
						}
						break;

					case 1:
						
						for (int i = 0;i < PEKA_NUMBER;i++) {
							if (peks[i]->mHealth > 0) {
								peks[i]->render(gRen, gPekTexture, pekClip, facing, player->getPosX());
							}
						}
						break;
					case 2:
						/*boss.fight(player->getPosX(), player->getPosY(), *player);
						boss.fight(hog.getPosX(), hog.getPosY(), hog);
						boss.fight(val.getPosX(), val.getPosY(), val);
						boss.fight(knight.getPosX(), knight.getPosY(), knight);*/

						switch (boss.mStatus) {
						case 0:
							gBossTex = gBossIdleTex;
							bossCurrClip = &gBossIdleSprites[bossStartFrame / 15];
							lastBossFrame = IDLE_FRAMES;
							break;
						case 2:
							gBossTex = gBossAtk1Tex;
							bossCurrClip = &gBossAtk1Sprites[bossStartFrame / 4];
							lastBossFrame = ATK1_FRAMES;
							break;
						case 3:
							gBossTex = gBossAtk2Tex;
							bossCurrClip = &gBossAtk2Sprites[bossStartFrame / 4];
							lastBossFrame = ATK2_FRAMES;
							break;

						}

						if (boss.mHealth > 0)boss.render(gRen, gBossTex, bossCurrClip, facing, player->getPosX());
						else deathes++;
						int tmpRan = makeRandomNum() % 2;
						//cout << tmpRan << endl;
						//fires every 20 seconds
						
						if (tmp % 20 == 0 && tmp!=0 && tmpRan == 0) {
							
							Dot laser(player->getPosX()-60, player->getPosY() - 920, 160, 960, 10000, 10, 5);
							laser.render(gRen, gLaserTex, currLaserClip,SDL_FLIP_NONE);
							player->hurt(laser.getCollider(), laser);
						}
						break;
					}

					if (chance == 0) {
						for (int i = 0;i < 5;i++) {
							hearts[i]->save(*player);
							if (checkCollision(player->getCollider(), hearts[i]->getCollider()))score -= 50;
						}
					}

					//cout << player->getStatus() << endl;
					if (player->mHealth > 0)player->render(gRen, gPlayerTexture, currentClip, flipType);

					//int currHP = (player->mHealth / playerHP) * 100;
					int currHP = double(player->mHealth)/double(playerHP) * 100;
					//currHP / 10;
					//cout << currHP << endl;
					HP.x = player->getPosX();
					HP.y = player->getPosY() - HP.h-3;
					if (currHP > 0 && currHP <= 100) {
						HP.w = currHP;
					}
					else if (currHP > 100) {
						HP.w = 100;
					}
					else {
						HP.w = 0;
					}
					

					if (chance == 0) {
						for (int i = 0;i < 5;i++) {
							hearts[i]->render(gRen, gHeartTex, NULL, SDL_FLIP_NONE);
						}
					}
					//cout << hog.getPosX() << " " << val.getPosX() << " " << knight.getPosX() << " " << player.getPosX() << endl;
					//cout << player.mDamage << endl;
					// 
					//cout << player.mHealth << endl;
					for (int i = 0;i < 150;++i) {
						tileset[i]->render(gRen, gTileTex, gTile[tileset[i]->getType()]);
					}

					
					if (deathes >= currDeathes) {
						p = { SCRW - 32,SCRH - 32,32,32 };
						gPortalTex.render(gRen, SCRW - 32, SCRH - 32, portalClip);
						portalFrame++;
						if (portalFrame / PORTAL_FRAMES >= PORTAL_FRAMES)portalFrame = 0;
					}

					SDL_SetRenderDrawColor(gRen, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(gRen, &HP);
					
					SDL_RenderPresent(gRen);
					//cout << player.mHealth << endl;
					// 
					cout << tmp << " " << boss.mStatus << " " << boss.mHealth << endl;;
					//cout << player->mStamina << endl;
					
					++startframe;
					++datFrame;
					++pekFrame;
					++idleFrame;
					++bossStartFrame;
					++laserFrame;
					//cout << bossStartFrame << endl;
					if (startframe / 4 >= lastFrame) startframe = 0;
					if (datFrame / GOBLIN_FRAMES >= GOBLIN_FRAMES) datFrame = 0;
					if (pekFrame / PEKA_FRAMES >= PEKA_FRAMES)pekFrame = 0;

					if (bossStartFrame / lastBossFrame >= lastBossFrame)bossStartFrame = 0;

					if (laserFrame / 1 >= LASER_FRAMES)laserFrame = 0;
					
					//cout << stopTimer.getTicks() / 1000.f << endl;
					if (checkCollision(player->getCollider(), p)) {

						/*if (level == 3) {

							//DrawEndGameSelection(gLoseTex, &e, gRen, playAgain);
						}*/

						if (stopTimer.getTicks() / 1000.f < 120) {
							score += 500;
						}
						else if (stopTimer.getTicks() / 1000.f > 120 && stopTimer.getTicks() / 1000.f < 300) {
							score += 200;
						}

						/*score += deathes * 100;
						if (level == 2)score += deathes * 1000;*/
						switch (level) {
						case 0:
							score += deathes * 100;
							break;
						case 1:
							score += deathes * 200;
							break;
						case 2:
							score += 10000;
							break;
						}
						level++;
						if (level == 3) {
							quit = true;
							break;
						}
						
						chance = randNumGen() % 6;
						if (chance == 0) {
							for (int i = 0;i < 5;i++) {
								hearts[i] = new Dot(randNumGen() % SCRW, randNumGen() % SCRH, 20, 20);
							}
						}

						stopTimer.start();

						currDeathes = DEATH[level];

						setTiles(tileset, levels[level]);
					}
				}
				
				if (level != 3) {
					switch (level) {
					case 0:
						score += deathes * 100;
						break;
					case 1:
						score += deathes * 200;
						break;
					case 2:
						score += 10000;
						break;
					}

					writeHighScore("high.txt", score);
					DrawEndGameSelection(gLoseTex, &e, gRen, playAgain);
				}
				else {

					handleGambling(score);
					writeHighScore("high.txt", score);
					if(score>0)DrawEndGameSelection(gWinTex, &e, gRen, playAgain);
					else DrawEndGameSelection(gLoseTex, &e, gRen, playAgain);
					
				}
			}
			

			//-----
		}
		
	}

	close();
	return 0;
}



bool init() {
	bool success = true;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWin = SDL_CreateWindow("CHUD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);
	gRen = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(gRen, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;

	IMG_Init(imgFlags)& imgFlags;

	TTF_Init();

	return success;
}


bool loadMedia(Tile* tiles[]) {
	bool success = true;

	
	gFont = TTF_OpenFont("clash.ttf", 25);
	
	if (!gTileTex.loadFromFile("wall.png", gRen)) {
		printf("Cant load wall \n");
		success = false;
	}

	if (!gHogTexture.loadFromFile("cogrider.png",gRen)) {
		printf("cant load hog\n");
		success = false;
	}

	if (!gValTexture.loadFromFile("valkyrie.png", gRen)) {
		printf("cant load val\n");
		success = false;
	}

	if (!gKnightTexture.loadFromFile("knight.png", gRen)) {
		printf("cant load knight\n");
		success = false;
	}
	if (!gDatTexture.loadFromFile("goblin.png", gRen)) {
		printf("cant load goblin\n");
		success = false;
	}
	if (!gPekTexture.loadFromFile("minipekka.png", gRen)) {
		printf("cant load pekka\n");
		success = false;
	}

	if (!gBossIdleTex.loadFromFile("idle.png", gRen)) {
		printf("cant load idle\n");
		success = false;
	}

	if (!gBossAtk1Tex.loadFromFile("attack1.png", gRen)) {
		printf("cant load atk1\n");
		success = false;

	}

	if (!gBossAtk2Tex.loadFromFile("attack2.png", gRen)) {
		printf("cant load atk2\n");
		success = false;
	}

	if (!gBossFlyTex.loadFromFile("fly.png", gRen)) {
		printf("cant load fly\n");
		success = false;
	}
	

	if (!gPortalTex.loadFromFile("portal.png", gRen)) {
		printf("cant load portal\n");
		success = false;
	}

	if (!gLaserTex.loadFromFile("laser.png", gRen)) {
		printf("cant load laser\n");
		success = false;
	}

	if (!gHeartTex.loadFromFile("heart.png", gRen)) {
		printf("cant load heart\n");
		success = false;
	}

	if (!gLoseTex.loadFromFile("lose.png", gRen)) {
		printf("cant load lose\n");
		success = false;
	}

	if (!gWinTex.loadFromFile("win.png", gRen)) {
		printf("cant load win\n");
		success = false;

	}

	if (!gPauseTex.loadFromFile("pause.png", gRen)) {
		printf("cant load pause\n");
		success = false;
	}
	
	if (!gPlayButtonTex.loadFromFile("play_button.png", gRen))
	{
		printf("cant load play button\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gPlayButton[i].x = 150 * i;
			gPlayButton[i].y = 0;
			gPlayButton[i].w = 150;
			gPlayButton[i].h = 98;
		}
	}

	if (!gBackButtonTex.loadFromFile("back_button.png", gRen))
	{
		printf("cant load back button\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gBackButton[i].x = 100 * i;
			gBackButton[i].y = 0;
			gBackButton[i].w = 100;
			gBackButton[i].h = 78;
		}
	}

	if (!gExitButtonTex.loadFromFile("exit_button.png", gRen))
	{
		printf("cant load exit button\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gExitButton[i].x = 150 * i;
			gExitButton[i].y = 0;
			gExitButton[i].w = 150;
			gExitButton[i].h = 98;
		}
	}

	if (!gPauseButtonTex.loadFromFile("pause_button.png", gRen))
	{
		printf("cant load pause button\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gPauseButton[i].x = 22 * i;
			gPauseButton[i].y = 0;
			gPauseButton[i].w = 22;
			gPauseButton[i].h = 34;
		}
	}

	if (!gContButtonTex.loadFromFile("continue_button.png", gRen))
	{
		printf("cant load cont button\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gContinueButton[i].x = 22 * i;
			gContinueButton[i].y = 0;
			gContinueButton[i].w = 22;
			gContinueButton[i].h = 34;
		}
	}

	if (!gMenuTex.loadFromFile("menu.png", gRen))
	{
		printf("cant load menu\n");
		success = false;
	}

	if (!gLoseTex.loadFromFile("lose.png", gRen))
	{
		printf("cant load lose\n");
		success = false;
	}

	if (!setTiles(tiles,"level1.map")) {
		printf("cant set tiles\n");
		success = false;
	}
	

	makeSprites(gHogIdleClips, HOG_IDLE_FRAMES, 30, 31);
	makeSprites(gHogMoveClips, HOG_MOVE_FRAMES, 30, 31, 120);
	makeSprites(gHogAtkClips, HOG_ATK_FRAMES, 30, 31, 360);
	

	makeSprites(gValIdleClips, VAL_IDLE_FRAMES, 31, 18);
	makeSprites(gValMoveClips, VAL_MOVE_FRAMES, 31, 18, 62);
	makeSprites(gValAtkClips, VAL_ATK_FRAMES, 31, 18, 155);

	makeSprites(gKnightIdleClips, KNIGHT_IDLE_FRAMES, 26, 24);
	makeSprites(gKnightMoveClips, KNIGHT_MOVE_FRAMES, 26, 24, 26 * 2);
	makeSprites(gKnightAtkClips, KNIGHT_ATK_FRAMES, 26, 24, 26 * 6);

	makeSprites(gDatSprites, GOBLIN_FRAMES, 12, 15);

	makeSprites(gPekSprites, PEKA_FRAMES, 27, 21);

	makeSprites(gBossIdleSprites, IDLE_FRAMES, 192, 112);
	makeSprites(gBossAtk1Sprites, ATK1_FRAMES, 192, 112);
	makeSprites(gBossAtk2Sprites, ATK2_FRAMES, 192, 112);
	makeSprites(gBossFlySprites, FLY_FRAMES, 192, 112);

	makeSprites(gLaserSprites, LASER_FRAMES, 160, 960);
	makeSprites(gPortalSprites, PORTAL_FRAMES, 32, 32);


	

	return success;
}

void close()
{
	gHogTexture.free();
	gValTexture.free();
	gKnightTexture.free();
	gDatTexture.free();

	gBossTex.free();
	
	gTileTex.free();
	gLaserTex.free();
	gPortalTex.free();
	
	TTF_CloseFont(gFont);
	gFont = NULL;

	SDL_DestroyRenderer(gRen);
	SDL_DestroyWindow(gWin);
	gWin = NULL;
	gRen = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}