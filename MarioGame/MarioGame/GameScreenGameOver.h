#pragma once
#ifndef _GAMESCREENGAMEOVER_H
#define _GAMESCREENGAMEOVER_H

#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include <iostream>

class GameScreenGameOver : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	GameScreenManager* gameScreenManager;
	bool SetUpLevel();
public:
	GameScreenGameOver(SDL_Renderer*, GameScreenManager*);
	~GameScreenGameOver();
	void Render();
};

#endif // !_GAMESCREENGAMEOVER_H

