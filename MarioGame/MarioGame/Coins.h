#pragma once
#include "Character.h"
class Coins : public Character
{
public:
	Coins(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	void Render();
	void Update(float deltaTime);
private:
	float mSingleSpriteWidth, mSingleSpriteHeight;
	int mFrameDelay;
	int mCurrentFrame;
	int mCurrentSprite;
};

