#include "GameScreenMenu.h"
#include "GameScreenManager.h"
#include "Texture2D.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{

}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

bool GameScreenMenu::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/MenuBackground.png"))
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}

	return true;
}