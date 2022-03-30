#include "GameScreen.h"
#include "GameInstance.h"
GameScreen::GameScreen()
{
}

GameScreen::~GameScreen()
{
}


void GameScreen::InitScreen(GameInstance* gameInstance)//called in onusercreate
{
}

void GameScreen::UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)
{
}

void GameScreen::ShowScreen()
{
	CanDisplayScreen = true;
}

void GameScreen::RemoveScreen()
{
	CanDisplayScreen = false;
}
