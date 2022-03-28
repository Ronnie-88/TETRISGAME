#pragma once
#include "olcPixelGameEngine.h"
#include"GameScreen.h"
#include <iostream>

class GameInstance : public olc::PixelGameEngine
{
public:
	GameInstance();
	~GameInstance();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void SwitchScreen(GameScreen* newScreen);
	GameScreen* GetGameLevel();
	GameScreen* GetMenuLevel();
	GameScreen* GetGameOverLevel();
	void AddToScore(const int& numOfLinesCleared);
	const int& GetCurrentScore();
	const int& GetNumOfLinesCleared();
	void ResetScoreAndLines();
private:
	GameScreen* currentScreenToDisplay = nullptr;
	GameScreen* gameLevel = nullptr;
	GameScreen* menuLevel = nullptr;
	GameScreen* gameOverScreen = nullptr;
	unsigned int currentScore = 0;
	unsigned int numOfLinesCleared = 0;
};

