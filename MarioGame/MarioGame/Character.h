#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include <string>
#include "Texture2D.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "Constants.h"
using namespace std;

class Texture2D;
class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Vector2D mRespawnPosition;
	Texture2D* mTexture;

	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool alive;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void AddGravity(float deltaTime);
	void Jump();

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }

	bool mCanJump;
	bool mJumping;
	float mJumpForce;
	float mCollisionRadius;

	bool isJumping() { return mJumping; }
	void CancelJump() { mJumping = false; }

	void SetAlive(bool isAlive);
	bool GetAlive() { return alive; }

	Vector2D CharacterRespawn() { return mRespawnPosition; }

private:
	LevelMap* mCurrentLevelMap;
};
