#include "GameScreenLevel0.h"
#include "QuestionBlock.h"

GameScreenLevel0::GameScreenLevel0(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
}

GameScreenLevel0::~GameScreenLevel0()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete myCharacter1;
	myCharacter1 = NULL;

	delete myCharacter2;
	myCharacter2 = NULL;

	delete mQuestionBlock;
	mQuestionBlock = NULL;

	mGoombas.clear();
}

void GameScreenLevel0::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	myCharacter1->Render();
	myCharacter2->Render();
	mQuestionBlock->Render();

	for (unsigned int i = 0; i < mGoombas.size(); i++)
	{
		mGoombas[i]->Render();
	}

	//Draw coins
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenLevel0::Update(float deltaTime, SDL_Event e)
{
	UpdateQuestionBlock(deltaTime);
	myCharacter1->Update(deltaTime, e);
	myCharacter2->Update(deltaTime, e);

	UpdateGoomba(deltaTime, e);
	UpdateCoins(deltaTime, e);
}


void GameScreenLevel0::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1} };

	//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);
}

bool GameScreenLevel0::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	//Create the new level map
	SetLevelMap();
	// Set up the player character
	myCharacter1 = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	myCharacter2 = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(32, 330), mLevelMap);
	if (!mBackgroundTexture->LoadFromFile("Images/Level0BackgroundTest.png"))
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}

	mQuestionBlock = new QuestionBlock(mRenderer, mLevelMap);

	//Set up enemies and coins
	CreateGoomba(Vector2D(260, 240), FACING_LEFT, MOVEMENT_SPEED);

	CreateCoins(Vector2D(203, 260));
	CreateCoins(Vector2D(233, 260));
	CreateCoins(Vector2D(263, 260));
	CreateCoins(Vector2D(293, 260));
	coinsCollected = 0;

	return true;
}

void GameScreenLevel0::UpdateQuestionBlock(float deltaTime)
{
	mQuestionBlock->Update(deltaTime);
	if (Collisions::Instance()->Box(mQuestionBlock->GetCollisionBox(), myCharacter1->GetCollisionBox()))
	{
		if (mQuestionBlock->IsAvailable())
		{
			mQuestionBlock->TakeAHit();
			myCharacter1->CancelJump();
		}
	}

	if (Collisions::Instance()->Box(mQuestionBlock->GetCollisionBox(), myCharacter2->GetCollisionBox()))
	{
		if (mQuestionBlock->IsAvailable())
		{
			mQuestionBlock->TakeAHit();
			myCharacter2->CancelJump();
		}
	}
}

void GameScreenLevel0::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	CharacterGoomba* goombaCharacter = new CharacterGoomba(mRenderer, "Images/Goomba.png", mLevelMap, position, direction, speed);
	mGoombas.push_back(goombaCharacter);
}

void GameScreenLevel0::UpdateGoomba(float deltaTime, SDL_Event e)
{
	if (!mGoombas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mGoombas.size(); i++)
		{
			mGoombas[i]->Update(deltaTime, e);

			if ((mGoombas[i]->GetPosition().y > 300.0f || mGoombas[i]->GetPosition().y <= 0.0f) && (mGoombas[i]->GetPosition().x <= -32.0f || mGoombas[i]->GetPosition().x > SCREEN_WIDTH))
			{
				mGoombas[i]->SetAlive(false);
			}
			else
			{
				if (Collisions::Instance()->Circle(mGoombas[i], myCharacter1))
				{
					myCharacter1->SetPosition(myCharacter1->CharacterRespawn());
				}
				if (Collisions::Instance()->Circle(mGoombas[i], myCharacter2))
				{
					myCharacter2->SetPosition(myCharacter2->CharacterRespawn());
				}
			}

			if (!mGoombas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			mGoombas.erase(mGoombas.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel0::CreateCoins(Vector2D position)
{
	Coins* coin = new Coins(mRenderer, "Images/Coin.png", mLevelMap, position);
	mCoins.push_back(coin);
}

void GameScreenLevel0::UpdateCoins(float deltaTime, SDL_Event e)
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

void GameScreenLevel0::SoundEffects(string path)
{
	gCoin = Mix_LoadWAV(path.c_str());
	gPlayerDeath = Mix_LoadWAV(path.c_str());

	if (gCoin == NULL)
	{
		cout << "Failed to load coin sound effect! Error: " << Mix_GetError() << endl;
	}

	else
	{
		Mix_PlayChannel(-1, gCoin, 0);
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
