#include "GameScreenVictory.h"

GameScreenVictory::GameScreenVictory(SDL_Renderer* renderer, GameScreenManager* screenManager) : GameScreen(renderer)
{
	SetUpLevel();
	gameScreenManager = screenManager;
}

GameScreenVictory::~GameScreenVictory()
{

}

bool GameScreenVictory::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/VictoryBackground.png"))
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}
	return true;
}

void GameScreenVictory::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}