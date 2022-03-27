#include "GameInstance.h"

GameInstance::GameInstance()
{
	sAppName = "Tetris";
}

GameInstance::~GameInstance()
{
	//call delete screens
	//print();
	if (currentScreenToDisplay)
	{
		delete currentScreenToDisplay;
	}

	std::cout << "GameClosed" << std::endl;
}

bool GameInstance::OnUserCreate()
{
	gameLevel = new LevelScreen();
	currentScreenToDisplay = gameLevel;
	currentScreenToDisplay->InitScreen();
	return true;
}

bool GameInstance::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::DARK_CYAN);
	currentScreenToDisplay->UpdateScreen(this, fElapsedTime);
	return true;
}
