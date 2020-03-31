#pragma once
#ifndef _CHARACTERGOOMBA_
#define _CHARACTERGOOMBA_

#include "Character.h"

class CharacterGoomba : public Character
{
public:
	CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:
	float mSingleSpriteWidth, mSingleSpriteHeight, mMovementSpeed;
	int mFrameDelay;
	int mCurrentFrame;
	int mCurrentSprite;
};

#endif // !_CHARACTERGOOMBA_