#pragma once
#ifndef _CHARACTERMARIO_
#define _CHARACTERMARIO_

#include "Character.h"
#include "Constants.h"
#include "GameScreenLevel1.h"
class CharacterMario :public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();
	void Update(float deltaTime, SDL_Event e);
};

#endif // !_CHARACTERMARIO_
