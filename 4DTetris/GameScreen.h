#pragma once
#include "olcPixelGameEngine.h"
#include "Tetramino.h"
class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void ShowScreen();//shows the current screen to display
	virtual void RemoveScreen();

private:

};

