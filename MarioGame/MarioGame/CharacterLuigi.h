#pragma once
#ifndef _CHARACTERLUIGI_
#define _CHARACTERLUIGI_

#include "Character.h"
#include "Constants.h"
#include "LevelMap.h"
class CharacterLuigi :public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();
	void Update(float deltaTime, SDL_Event e);
};

#endif // !_CHARACTERLUIGI_
