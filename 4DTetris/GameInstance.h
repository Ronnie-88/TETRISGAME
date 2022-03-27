#pragma once
#include "olcPixelGameEngine.h"
#include"GameScreen.h"
#include "LevelScreen.h"
#include <iostream>

class GameInstance : public olc::PixelGameEngine
{
public:
	GameInstance();
	~GameInstance();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
private:
	GameScreen* currentScreenToDisplay = nullptr;
	GameScreen* gameLevel = nullptr;
};

