#pragma once
#ifndef _CHARACTERKOOPA_
#define _CHARACTERKOOPA_

#include "Character.h"

class CharacterKoopa :  public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:
	float mSingleSpriteWidth, mSingleSpriteHeight, mInjuredTime, mMovementSpeed;
	bool mInjured;
	
	void FlipRightWayUp();
};

#endif // !_CHARACTERKOOPA_