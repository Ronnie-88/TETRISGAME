#include "GameInstance.h"
#include "MenuScreen.h"
#include "LevelScreen.h"
#include "GameOverScreen.h"
GameInstance::GameInstance()
{
	sAppName = "Tetris";
}

GameInstance::~GameInstance()
{
	delete gameLevel;
	delete menuLevel;
	delete gameOverScreen;
	std::cout << "GameClosed" << std::endl;
}

bool GameInstance::OnUserCreate()
{
	menuLevel = new MenuScreen();
	gameLevel = new LevelScreen();
	gameOverScreen = new GameOverScreen();
	SwitchScreen(menuLevel);
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
		currentScreenToDisplay->InitScreen(this);
		currentScreenToDisplay->ShowScreen();
		return;
	}

	currentScreenToDisplay->RemoveScreen();
	currentScreenToDisplay = newScreen;
	currentScreenToDisplay->InitScreen(this);
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

void GameInstance::AddToScore(const int& numOfLinesCleared)
{
	if (numOfLinesCleared == 0)//award points for landing a tetramino
	{
		currentScore += 15;
	}
	else if(numOfLinesCleared > 0 && numOfLinesCleared < 4)//award points for clearing less than 4 lines 
	{
		currentScore += 100;
	}
	else if(numOfLinesCleared >= 4)//Tetris Baby!!!
	{
		currentScore += 800;
	}
	this->numOfLinesCleared += numOfLinesCleared;
}

const int& GameInstance::GetCurrentScore()
{
	return currentScore;
}

const int& GameInstance::GetNumOfLinesCleared()
{
	return numOfLinesCleared;
}

void GameInstance::ResetScoreAndLines()
{
	currentScore = 0;
	numOfLinesCleared = 0;
}
