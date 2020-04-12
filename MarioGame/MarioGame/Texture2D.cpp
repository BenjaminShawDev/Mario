#include "Texture2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GameScreen.h"
#include "GameScreenLevel1.h"
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;

	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{

	//Remove the memory used for a previous texture
	Free();
	

	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		
		
		//Colour key the image - The colour to be transparent
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		//Create the texture from the pixels on the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		
		if (mTexture == NULL)
		{
			//Remove the loaded surface now that we have the texture
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;

		}
		else
		{
			//Set the dimensions
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from the surface. Error: " << IMG_GetError() << endl;
	}


	//Return whether the process was successful
	return mTexture != NULL;
}



void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{

	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);

}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}