#include "GameScreenGameOver.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, GameScreenManager* screenManager) : GameScreen(renderer)
{
	SetUpLevel();
	gameScreenManager = screenManager;	
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

bool GameScreenGameOver::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/GameOverBackground.png"))
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}
	return true;
}

void GameScreenGameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}