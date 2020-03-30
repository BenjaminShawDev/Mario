#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
	alive = true;
	mRespawnPosition = startPosition;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE);
	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (mJumping)
	{
		//Adjust the position
		mPosition.y -= mJumpForce * deltaTime;
		//Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		//Has the jump force reduced to zero
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (mMovingLeft)
		MoveLeft(deltaTime);
	else if (mMovingRight)
		MoveRight(deltaTime);

	//int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	int headPosition = (int)(mPosition.y) / TILE_HEIGHT;
	int sidePosition = (int)(mPosition.y + (mTexture->GetHeight() * 0.5f)) / TILE_HEIGHT;
	int leftXPosition = (int)(mPosition.x) / TILE_WIDTH;
	int rightXPosition = (int)(mPosition.x + (mTexture->GetWidth())) / TILE_WIDTH;
	int testPosition = (int)(mPosition.y + mTexture->GetHeight()) / (TILE_HEIGHT / 3);

	//Deal with gravity
	if (mCurrentLevelMap->GetTileAt(footPosition, leftXPosition) == 0 && mCurrentLevelMap->GetTileAt(footPosition, rightXPosition) == 0)
	{
		AddGravity(deltaTime);
	}

	else
	{
		//Collided with ground so we can jump again
		mCanJump = true;
	}

	//Head collision with block
	if (mCurrentLevelMap->GetTileAt(headPosition, leftXPosition) == 1 || mCurrentLevelMap->GetTileAt(headPosition, rightXPosition) == 1)
	{
		mJumping = false;
	}

	//Edge collision with block (left)
	if (mCurrentLevelMap->GetTileAt(sidePosition, leftXPosition) == 1 || mCurrentLevelMap->GetTileAt(sidePosition, leftXPosition) == 2)
	{
		mPosition.x += 0.1;
		AddGravity(deltaTime);
	}

	//Edge collision with block (right)
	else if (mCurrentLevelMap->GetTileAt(sidePosition, rightXPosition) == 1 || mCurrentLevelMap->GetTileAt(sidePosition, rightXPosition) == 2)
	{
		mPosition.x -= 0.1;
		AddGravity(deltaTime);
	}

	if (mPosition.y > 450.0f)
	{
		SetPosition(CharacterRespawn());
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= deltaTime * MOVEMENT_SPEED;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += deltaTime * MOVEMENT_SPEED;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump()
{
	if (mCanJump == true)
	{
		if (!mJumping)
		{
			mJumpForce = INITIAL_JUMP_FORCE;
			mJumping = true;
			mCanJump = false;
		}
	}
	//Collided with ground so we can jump
	else
		mCanJump = true;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

void Character::SetAlive(bool isAlive)
{
	alive = isAlive;
}

void Character::SoundEffect(string path)
{
	gSoundEffect = Mix_LoadWAV(path.c_str());

	if (gSoundEffect == NULL)
	{
		cout << "Failed to loud sound effect! Error: " << Mix_GetError() << endl;
	}

	else if (mCanJump == false)
	{
		Mix_PlayChannel(-1, gSoundEffect, 0);
	}
}
