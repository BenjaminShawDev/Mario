#include "GameScreenLevel0.h"

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
}

void GameScreenLevel0::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	myCharacter1->Render();
	myCharacter2->Render();

	//Draw coins
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
}

void GameScreenLevel0::Update(float deltaTime, SDL_Event e)
{
	myCharacter1->Update(deltaTime, e);
	myCharacter2->Update(deltaTime, e);

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
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

	//Set up enemies and coins
	CreateCoins(Vector2D(200, 350));
	CreateCoins(Vector2D(220, 350));
	CreateCoins(Vector2D(240, 350));
	CreateCoins(Vector2D(260, 350));
	CreateCoins(Vector2D(280, 350));
	coinsCollected = 0;

	return true;
}

void GameScreenLevel0::UpdateEnemies()
{

}

void GameScreenLevel0::CreateKoopa(Vector2D position, FACING direction)
{

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
