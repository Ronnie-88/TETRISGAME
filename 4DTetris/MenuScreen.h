#pragma once
#include "GameScreen.h"
class MenuScreen :public GameScreen
{
public:
	MenuScreen();
	~MenuScreen();
public:
	void InitScreen() override;
};

