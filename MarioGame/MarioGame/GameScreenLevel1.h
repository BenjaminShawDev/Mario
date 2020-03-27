#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "Coins.h"
#include <vector>

class Texture2D;
class Character;
class PowBlock;
class CharacterMario;
class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	
	CharacterMario* myCharacter1;
	CharacterLuigi* myCharacter2;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	bool SetUpLevel();

	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	int respawnTime;
	int coinsCollected;
	vector<CharacterKoopa*> mEnemies;
	vector<Coins*> mCoins;
	
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();
	void UpdatePowBlock();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoins(Vector2D position);
};

#endif // !_GAMESCREENLEVEL1_H



