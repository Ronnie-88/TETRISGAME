#pragma once
#include "GameScreen.h"
#include<iostream>

class MenuScreen :public GameScreen
{
public:
	MenuScreen();
	~MenuScreen();
public:
	void UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)override;
	void DrawTitleAndCredits(GameInstance* gameInstance) const;
	void DrawButton(GameInstance* gameInstance, const bool& hoverState)const;
	void InitScreen(GameInstance* gameInstance) override;
	const bool& IsMouseHovering()const;
	void OnMouseButtonClicked(GameInstance* gameInstance, const bool& bMouseHoverstatus)const;
private:
	olc::vi2d buttonPos;
	olc::vi2d buttonSize;
	olc::vf2d mousePos;
	std::string TitleText = "Tetris";
	std::string StartButtonText = "Start";
	std::string CreditsText = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tCreated by Ronald Kamanga\n(Not originally! That Honour goes to Mr. Alexey Pajitnov)";
	olc::Pixel DefaultButtonColour = olc::WHITE;
	olc::Pixel HoverButtonColour = olc::GREY;
};

