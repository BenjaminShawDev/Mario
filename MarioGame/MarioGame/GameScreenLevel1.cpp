#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"
#include "GameScreenManager.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete myCharacter1;
	myCharacter1 = NULL;

	delete myCharacter2;
	myCharacter2 = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
}


void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	myCharacter1->Render();
	myCharacter2->Render();
	mPowBlock->Render();
	
	//Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	//Draw coins
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the shake after the duration
		if (mScreenShakeTime <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//if (Collisions::Instance()->Circle(myCharacter1, myCharacter2))
			//Update the player
	myCharacter1->Update(deltaTime, e);
	myCharacter2->Update(deltaTime, e);


	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
										{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

	//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	//Create the level map
	SetLevelMap();
	//Set up the player character
	myCharacter1 = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	myCharacter2 = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(416, 330), mLevelMap);
	if (!mBackgroundTexture->LoadFromFile("Images/Level1Background.png"))
	{
		cout << "Failed to load background texture" << endl;;
		return false;
	}

	//Set up our POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//Set up 2 bad guys
	CreateKoopa(Vector2D(64, 32), FACING_RIGHT, MOVEMENT_SPEED);
	CreateKoopa(Vector2D(416, 32), FACING_LEFT, MOVEMENT_SPEED);

	//Set up coins
	CreateCoins(Vector2D(200, 350));
	CreateCoins(Vector2D(220, 350));
	CreateCoins(Vector2D(240, 350));
	CreateCoins(Vector2D(260, 350));
	CreateCoins(Vector2D(280, 350));
	coinsCollected = 0;

	return true;
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacter1->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (myCharacter1->isJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				myCharacter1->CancelJump();
				SoundEffects("Music/POWBlock.wav");
			}
		}
	}

	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacter2->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (myCharacter2->isJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				myCharacter2->CancelJump();
				SoundEffects("Music/POWBlock.wav");
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURARTION;
	mWobble = 0.0f;

	for (int i = 0; i < mEnemies.size(); i++)
		mEnemies[i]->TakeDamage();
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			////Check if enemy is on the bottom row of tiles
			//if (mEnemies[i]->GetPosition().y > 300.0f)
			//{
			//	//Is the enemy off the screen to the left/right?
			//	if ((mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f)))
			//	{
			//		//mEnemies[i]->SetAlive(false);
			//		//Setip respawn time
			//		mEnemies[i]->SetPosition(mEnemies[i]->CharacterRespawn());
			//	}
			//}

			//Now do the update
			mEnemies[i]->Update(deltaTime, e);

			//Check to see if the enemy collides with the player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], myCharacter1))
				{
					SoundEffects("Music/PlayerDeath.wav");
					myCharacter1->SetPosition(myCharacter1->CharacterRespawn());
				}
				if (Collisions::Instance()->Circle(mEnemies[i], myCharacter2))
				{
					SoundEffects("Music/PlayerDeath.wav");
					myCharacter2->SetPosition(myCharacter2->CharacterRespawn());
				}
			}

			//If the enemy is no longer alive, then schedule it for deletion
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove a dead enemy
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}

	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!mCoins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			
			mCoins[i]->Update(deltaTime);
			if ((mCoins[i]->GetPosition().y > 300.0f || mCoins[i]->GetPosition().y <= 64.0f) && (mCoins[i]->GetPosition().x < 64.0f || mCoins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Something
			}

			else
			{
				if (Collisions::Instance()->Circle(mCoins[i], myCharacter1))
				{
					mCoins[i]->SetAlive(false);
					coinsCollected += 1;
					cout << "Coins: " << coinsCollected << endl;
					SoundEffects("Music/Coin.wav");
				}
				if (Collisions::Instance()->Circle(mCoins[i], myCharacter2))
				{
					mCoins[i]->SetAlive(false);
					coinsCollected += 1;
					cout << "Coins: " << coinsCollected << endl;
					SoundEffects("Music/Coin.wav");
				}
			}

			if (!mCoins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoins(Vector2D position)
{
	Coins* coin = new Coins(mRenderer, "Images/Coin.png", mLevelMap, position);
	mCoins.push_back(coin);
}

void GameScreenLevel1::SoundEffects(string path)
{
	gCoin = Mix_LoadWAV(path.c_str());
	gPOWBlock = Mix_LoadWAV(path.c_str());
	gPlayerDeath = Mix_LoadWAV(path.c_str());

	if (gCoin == NULL)
	{
		cout << "Failed to load coin sound effect! Error: " << Mix_GetError() << endl;
	}

	else
	{
		Mix_PlayChannel(-1, gCoin, 0);
	}

	if (gPOWBlock == NULL)
	{
		cout << "Failed to load POW sound effect! Error: " << Mix_GetError() << endl;
	}

	else 
	{
		Mix_PlayChannel(-1, gPOWBlock, 0);
	}

	if (gPlayerDeath == NULL)
	{
		cout << "Failed to load player death sound effect! Error: " << Mix_GetError() << endl;
	}

	else
	{
		Mix_PlayChannel(-1, gPlayerDeath, 0);
	}
}