#pragma once
#ifndef _GAMESCREENLEVEL0_H
#define _GAMESCREENLEVEL0_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "CharacterGoomba.h"
#include "Coins.h"
#include <vector>

class Texture2D;
class Character;
class CharacterMario;
class QuestionBlock;

class GameScreenLevel0 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	CharacterMario* myCharacter1;
	CharacterLuigi* myCharacter2;
	LevelMap* mLevelMap;
	QuestionBlock* mQuestionBlock;
	Mix_Chunk* gCoin;
	Mix_Chunk* gPlayerDeath;

	bool SetUpLevel();

	int coinsCollected;

	vector<CharacterGoomba*> mGoombas;
	vector<Coins*> mCoins;

public:
	GameScreenLevel0(SDL_Renderer* renderer);
	~GameScreenLevel0();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();
	void UpdateQuestionBlock(float deltaTime);
	void UpdateGoomba(float deltaTime, SDL_Event e);
	void CreateGoomba(Vector2D position, FACING direction, float speed);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoins(Vector2D position);
	void SoundEffects(string path);
};

#endif // !_GAMESCREENLEVEL0_H