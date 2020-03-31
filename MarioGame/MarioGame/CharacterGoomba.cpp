#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mPosition = startPosition;
	mMovementSpeed = movementSpeed;
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
	mFrameDelay = 0;
	mCurrentFrame = 0;
	mCurrentSprite = 0;
}

void CharacterGoomba::Render()
{
	SDL_Rect portionOfSpriteSheet = { mCurrentSprite, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	mMovingLeft = true;
	mMovingRight = false;

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;
		mCurrentFrame++;

		if (mCurrentFrame > 1)
			mCurrentFrame = 0;
	}

	if (mCurrentFrame == 0)
	{
		mCurrentSprite = 0;
	}

	else
	{
		mCurrentSprite = mSingleSpriteWidth;
	}
}
