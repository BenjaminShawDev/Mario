#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include "GameScreen.h"
#include <iostream>

class Texture2D;

class GameScreenMenu : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();
	void Render();
};

#endif // !_GAMESCREENMENU_H