#include "GameScreenLevel0.h"

GameScreenLevel0::GameScreenLevel0(SDL_Renderer* renderer, GameScreenManager* screenManager) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
	pipeAnimationDelay = 0;
	playerYPosition = 280;
	doPipeTransition = false;
	isMarioDead = false;
	isLuigiDead = false;
	gameScreenManager = screenManager;
	
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

	mCoins.clear();
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

	if (isMarioDead == true)
	{
		myCharacter1->SetPosition(Vector2D(-40, -40));
	}
	if (isLuigiDead == true)
	{
		myCharacter2->SetPosition(Vector2D(-40, -40));
	}

	if (isMarioDead == true && isLuigiDead == true)
	{
		gameScreenManager->ChangeScreen(SCREENS(SCREEN_GAMEOVER));
		return;
	}

	if (myCharacter1->GetPosition().x >= 430 && myCharacter1->GetPosition().x <= 450 && myCharacter1->GetPosition().y >= 270 || myCharacter2->GetPosition().x >= 430 && myCharacter2->GetPosition().x <= 450 && myCharacter2->GetPosition().y >= 270)
	{
		PipeLevelChange(deltaTime);
	}
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
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
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
	if (!mBackgroundTexture->LoadFromFile("Images/Level0Background.png"))
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}

	mQuestionBlock = new QuestionBlock(mRenderer, mLevelMap);
	//mLevelMap->ChangeTileAt(14, 13, 0);

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
			SoundEffects("Music/BlockHit.wav");
			myCharacter1->CancelJump();
			CreateCoins(Vector2D(264, 165));
		}
	}

	if (Collisions::Instance()->Box(mQuestionBlock->GetCollisionBox(), myCharacter2->GetCollisionBox()))
	{
		if (mQuestionBlock->IsAvailable())
		{
			mQuestionBlock->TakeAHit();
			SoundEffects("Music/BlockHit.wav");
			myCharacter2->CancelJump();
			CreateCoins(Vector2D(264, 165));
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
					SoundEffects("Music/PlayerDeath.wav");
					//myCharacter1->SetPosition(myCharacter1->CharacterRespawn());
					isMarioDead = true;
					myCharacter1->SetPosition(Vector2D(-40, -40));
				}
				if (Collisions::Instance()->Circle(mGoombas[i], myCharacter2))
				{
					SoundEffects("Music/PlayerDeath.wav");
					//myCharacter2->SetPosition(myCharacter2->CharacterRespawn());
					isLuigiDead = true;
					myCharacter2->SetPosition(Vector2D(-40, -40));
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
					SoundEffects("Music/Coin.wav");
				}
				if (Collisions::Instance()->Circle(mCoins[i], myCharacter2))
				{
					mCoins[i]->SetAlive(false);
					coinsCollected += 1;
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
	gBlockHit = Mix_LoadWAV(path.c_str());
	gPipe = Mix_LoadWAV(path.c_str());

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

	if (gBlockHit == NULL)
	{
		cout << "Failed to load block hit sound effect! Error: " << Mix_GetError() << endl;
	}

	else
	{
		Mix_PlayChannel(-1, gBlockHit, 0);
	}

	if (gPipe == NULL)
	{
		cout << "Failed to load pipe sound effect! Error: " << Mix_GetError() << endl;
	}

	else
	{
		Mix_PlayChannel(-1, gPipe, 0);
	}
}

void GameScreenLevel0::PipeLevelChange(float deltaTime)
{
	if (!isMarioDead)
	{
		myCharacter1->SetPosition(Vector2D(449, playerYPosition));
		myCharacter1->CancelJump();
	}
	if (!isLuigiDead)
	{
		myCharacter2->SetPosition(Vector2D(434, playerYPosition));
		myCharacter2->CancelJump();
	}
	if (doPipeTransition == false)
	{
		SoundEffects("Music/Pipe.wav");
		doPipeTransition = true;
	}
	pipeAnimationDelay -= deltaTime;
	if (pipeAnimationDelay <= 0.0f)
	{
		pipeAnimationDelay = PIPE_ANIMATION_DELAY / (deltaTime * 300);
		playerYPosition++;
		playerYPosition++;
	}

	if (playerYPosition >= 450 && doPipeTransition)
	{
		doPipeTransition = false;
		playerYPosition = NULL;
		myCharacter1->SetPosition(Vector2D(64, 330));
		myCharacter2->SetPosition(Vector2D(32, 330));

		gameScreenManager->ChangeScreen(SCREENS(SCREEN_LEVEL1));
	}
}