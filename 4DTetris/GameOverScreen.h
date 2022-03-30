#pragma once
#include "GameScreen.h"
class GameOverScreen : public GameScreen
{
public:
	GameOverScreen();
	~GameOverScreen();
public:
	void UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)override;
	void DrawGameOverAndScore(GameInstance* gameInstance)const;
	void DrawButton(GameInstance* gameInstance, const bool& hoverState)const;
	void InitScreen(GameInstance* gameInstance) override;
	const bool& IsMouseHovering()const;
	void OnMouseButtonClicked(GameInstance* gameInstance, const bool& bMouseHoverstatus)const;
private:
	olc::vi2d buttonPos;
	olc::vi2d buttonSize;
	olc::vf2d mousePos;
	std::string TitleText = "Game Over";
	std::string ScoreText = "Your Score: ";
	std::string MenuButtonText = "Main Menu";
	olc::Pixel DefaultButtonColour = olc::WHITE;
	olc::Pixel HoverButtonColour = olc::GREY;
};

