#pragma once
#ifndef _GAMESCREENVICTORY
#define _GAMESCREENVICTORY

#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include <iostream>

class GameScreenVictory : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	GameScreenManager* gameScreenManager;
	bool SetUpLevel();
public:
	GameScreenVictory(SDL_Renderer*, GameScreenManager*);
	~GameScreenVictory();
	void Render();
};

#endif // !_GAMESCREENVICTORY

