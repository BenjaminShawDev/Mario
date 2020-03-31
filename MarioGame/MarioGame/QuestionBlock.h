#pragma once
#include "GameScreenLevel0.h"

class QuestionBlock
{
public:
	QuestionBlock(SDL_Renderer* renderer, LevelMap* map);
	~QuestionBlock();
	void Render();
	void Update(float deltaTime);
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x - 40, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight() + 33); }
	void TakeAHit();
	bool IsAvailable() { return mHasBeenHit == false; }
	
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mHasBeenHit;
	int mFrameDelay, mCurrentFrame, mCurrentSprite;
};

