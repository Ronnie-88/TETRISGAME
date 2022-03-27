#pragma once
#include "olcPixelGameEngine.h"
#include "Tetramino.h"
class GameScreen
{
public:
	GameScreen();
	virtual ~GameScreen();

	virtual void InitScreen();
	virtual void UpdateScreen(olc::PixelGameEngine* gameInstance, const float& fElapsedTime);//shows the current screen to display
	void RemoveScreen();//removes the current screen from display

protected:
	bool CanDisplayScreen = true;
};

