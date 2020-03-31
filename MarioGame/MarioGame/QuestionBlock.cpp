#include "QuestionBlock.h"

QuestionBlock::QuestionBlock(SDL_Renderer* renderer, LevelMap* map)
{
	string imagePath = "Images/QuestionBlockTest2.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 4;
	mSingleSpriteHeight = mTexture->GetHeight();
	mHasBeenHit = false;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f + 16) - mSingleSpriteWidth * 0.5f, 192);
	mFrameDelay = 0;
}

QuestionBlock::~QuestionBlock()
{
	mRenderer = NULL;
	delete[] mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void QuestionBlock::Update(float deltaTime)
{
	if (mHasBeenHit == false)
	{
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0)
		{
			mFrameDelay = ANIMATION_DELAY;
			mCurrentFrame++;
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

	else
	{
		mCurrentSprite = mSingleSpriteWidth * 3;
	}
}

void QuestionBlock::Render()
{
	SDL_Rect portionOfSpriteSheet = { mCurrentSprite, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

void QuestionBlock::TakeAHit()
{
	cout << "HIT!" << endl;
	mHasBeenHit = true;
}