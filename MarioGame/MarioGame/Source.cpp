#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "GameScreenLevel0.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
using namespace std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
Mix_Music* gMusic = NULL;
GameScreenLevel0* gameScreenTest;
class GameScreenLevel0;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path); 

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		//Set up the game screen manager
		gameScreenManager = new GameScreenManager(gRenderer, SCREENS(SCREEN_MENU));

		LoadMusic("Music/Mario.mp3");
		gOldTime = SDL_GetTicks();

		//Flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	//Close Window and free resources
	CloseSDL();
	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError() << endl;
		return false;
	}

	//Initialise the Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise! Error: " << Mix_GetError();
		return false;
	}

	else
	{
		//All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError() << endl;;
			return false;
		}
		if (gRenderer != NULL)
		{
			//Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError() << endl;;
				return false;
			}
			//Load the background texture
			/*gTexture = new Texture2D(gRenderer);
			if (!gTexture->LoadFromFile("Images/test.bmp"))
			{
				return false;
			}*/
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError() << endl;;
			return false;
		}
	}
	return true;
}

void CloseSDL()
{
	// Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Clear the texture
	//FreeTexture();

	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	/*delete gTexture;
	gTexture = NULL;*/
}

bool Update()
{
	//Get the new line
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get the events
	SDL_PollEvent(&e);

	//Handle any events
	switch (e.type)
	{
		//Click the 'x' to quit
	case SDL_QUIT:
		return true;
	break;
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			gameScreenManager->ChangeScreen(SCREENS(SCREEN_LEVEL0));
			break;
		case SDLK_ESCAPE:
			exit(0);
			break;
		}
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	//Set the current time to be the old time
	gOldTime = newTime;

	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	
	/*gTexture->Render(Vector2D(), SDL_FLIP_NONE);*/
	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}

}