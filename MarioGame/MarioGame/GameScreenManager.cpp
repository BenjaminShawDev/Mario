#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel0.h"
#include "GameScreenLevel1.h"
#include "GameScreenGameOver.h"
#include "GameScreenVictory.h"

GameScreenMenu* tempScreenMenu;
GameScreenLevel0* tempScreen0;
GameScreenLevel1* tempScreen1;
GameScreenGameOver* tempGameOverScreen;
GameScreenVictory* tempVictoryScreen;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	//Ensure the screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	switch (newScreen)
	{
	case SCREEN_MENU:
		tempScreenMenu = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenMenu;
		tempScreenMenu = NULL;
		break;
	case SCREEN_LEVEL0:
		tempScreen0 = new GameScreenLevel0(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempScreen0;
		tempScreen0 = NULL;
		break;
	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_GAMEOVER:
		tempGameOverScreen = new GameScreenGameOver(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempGameOverScreen;
		tempGameOverScreen = NULL;
		break;
	case SCREEN_VICTORY:
		tempVictoryScreen = new GameScreenVictory(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempVictoryScreen;
		tempVictoryScreen = NULL;
		break;
	default:
		break;
	}
}
