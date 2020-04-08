#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{

}

CharacterMario::~CharacterMario()
{
	
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		case SDLK_w:
			Character::Jump();
			SoundEffect("Music/MarioJump.wav");
			break;
		case SDLK_ESCAPE:
			exit(0);
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		}
	}
	Character::Update(deltaTime, e);
}