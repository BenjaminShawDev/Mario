#include "LevelMap.h"

//0 = Empty area, 1 = Blocked area

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//Allocate memory for the level map
	mMap = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}

	//Populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//Delete all elements in the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] mMap[i];
	}
	delete[] mMap;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue)
{
	mMap[row][column] = newValue;
}
