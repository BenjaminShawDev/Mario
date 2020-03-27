#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2; //2 sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = SMALL_INITIAL_JUMP_FORCE;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//To gain the benefit of the code written in the base class Update() function we need to call it
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		
		//We are not injured so move
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingLeft = false;
			mMovingRight = true;
		}
	}
	else
	{
		//Should not move when injured
		mMovingLeft = false;
		mMovingRight = false;

		//Count the injured time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightWayUp();
	}
}

void CharacterKoopa::FlipRightWayUp()
{	
	mInjured = false;
	Jump();
}

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we draw
	int left = 0.0f;
	//If injured move the left position to be the left poisition on the second spritesheet
	if (mInjured)
		left = mSingleSpriteHeight;
	//Get the portion of the spritesheet you want to draw
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	//Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	//Then drawing it facing the correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}