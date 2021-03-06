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
	GameScreen* GetGameLevel()const;
	GameScreen* GetMenuLevel()const;
	GameScreen* GetGameOverLevel()const;
	void AddToScore(const int& numOfLinesCleared);
	const int& GetCurrentScore()const;
	const int& GetNumOfLinesCleared()const;
	void ResetScoreAndLines();
private:
	GameScreen* currentScreenToDisplay = nullptr;
	GameScreen* gameLevel = nullptr;
	GameScreen* menuLevel = nullptr;
	GameScreen* gameOverScreen = nullptr;
	unsigned int currentScore = 0;
	unsigned int numOfLinesCleared = 0;
};

