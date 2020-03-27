#include "Coins.h"

Coins::Coins(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition) : Character (renderer, imagePath, startPosition, map)
{
	mPosition = startPosition;
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mFrameDelay = 0;
	mCurrentFrame = 0;
	mCurrentSprite = 0;
}

void Coins::Render()
{

	SDL_Rect portionOfSpriteSheet = { mCurrentSprite, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

void Coins::Update(float deltaTime)
{
	//Change frame?
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		//Reset frame delay count
		mFrameDelay = ANIMATION_DELAY;

		//Move frame on
		mCurrentFrame++;

		//Loop frame around if it goes beyond the number of frames
		if (mCurrentFrame > 2)
			mCurrentFrame = 0;
	}

	if (mCurrentFrame == 0)
	{
		mCurrentSprite = 0;
	}

	else if (mCurrentFrame == 1)
	{
		mCurrentSprite = mSingleSpriteWidth;
	}

	else
	{
		mCurrentSprite = mSingleSpriteWidth * 2;
	}
}


