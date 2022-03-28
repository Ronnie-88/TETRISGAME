#pragma once
#include "olcPixelGameEngine.h"
class GameInstance;

class GameScreen
{
public:
	GameScreen();
	virtual ~GameScreen();
public:
	virtual void InitScreen(GameInstance* gameInstance);
	virtual void UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime);//shows the current screen to display
	virtual void ShowScreen();
	virtual void RemoveScreen();//removes the current screen from display

protected:
	bool CanDisplayScreen = false;
};

