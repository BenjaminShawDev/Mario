#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Rect2D
{
	float x;
	float y;
	float height;
	float width;

	Rect2D(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};

enum SCREENS
{
	SCREEN_MENU = 0,
	SCREEN_LEVEL0,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_VICTORY
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};