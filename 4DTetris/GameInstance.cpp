#include "GameInstance.h"
#include "LevelScreen.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
GameInstance::GameInstance()
{
	sAppName = "Tetris";
}

GameInstance::~GameInstance()
{
	//call delete screens
	//print();
	currentScreenToDisplay = nullptr;
	delete gameLevel;
	delete menuLevel;
	std::cout << "GameClosed" << std::endl;
}

bool GameInstance::OnUserCreate()
{
	menuLevel = new MenuScreen();
	gameLevel = new LevelScreen();
	gameOverScreen = new GameOverScreen();
	SwitchScreen(gameLevel);
	return true;
}

bool GameInstance::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::DARK_CYAN);
	currentScreenToDisplay->UpdateScreen(this, fElapsedTime);
	return true;
}

void GameInstance::SwitchScreen(GameScreen* newScreen)
{
	if (!currentScreenToDisplay)
	{
		currentScreenToDisplay = newScreen;
		currentScreenToDisplay->ShowScreen();
		return;
	}
	currentScreenToDisplay->RemoveScreen();
	currentScreenToDisplay = newScreen;
	currentScreenToDisplay->InitScreen();
	currentScreenToDisplay->ShowScreen();
}

GameScreen* GameInstance::GetGameLevel()
{
	return gameLevel;
}

GameScreen* GameInstance::GetMenuLevel()
{
	return menuLevel;
}

GameScreen* GameInstance::GetGameOverLevel()
{
	return gameOverScreen;
}
