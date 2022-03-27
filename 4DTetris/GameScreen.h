#pragma once
#include "olcPixelGameEngine.h"
class GameInstance;

class GameScreen
{
public:
	GameScreen();
	virtual ~GameScreen();
public:
	virtual void InitScreen();
	virtual void UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime);//shows the current screen to display
	void ShowScreen();
	void RemoveScreen();//removes the current screen from display

protected:
	bool CanDisplayScreen = false;
};

