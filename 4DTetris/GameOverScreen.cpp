#include "GameOverScreen.h"
#include"GameInstance.h"
#include"ScreenDimensions.h"
GameOverScreen::GameOverScreen()
{
	buttonPos = { (SCREEN_WIDTH / 2) - 60,300 };
	buttonSize = { 100,50 };
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)
{
	if (!CanDisplayScreen) { return; }
	mousePos.x = (float)gameInstance->GetMouseX();
	mousePos.y = (float)gameInstance->GetMouseY();
	DrawGameOverAndScore(gameInstance);
	DrawButton(gameInstance, IsMouseHovering());
	OnMouseButtonClicked(gameInstance, IsMouseHovering());
}

void GameOverScreen::DrawGameOverAndScore(GameInstance* gameInstance) const
{
	int xCoord = (SCREEN_WIDTH - gameInstance->GetTextSize(TitleText).x) / 2;
	int xCorrd2 = (SCREEN_WIDTH - gameInstance->GetTextSize(ScoreText + std::to_string(1000)).x) / 2;
	gameInstance->DrawStringDecal(olc::vi2d{ (xCoord - 150),100 }, TitleText, olc::WHITE, olc::vf2d{ 5.0f,10.0f });
	gameInstance->DrawStringDecal(olc::vi2d{ (xCorrd2 - 50),200 }, ScoreText + std::to_string(gameInstance->GetCurrentScore()), olc::BLACK, olc::vf2d{ 1.5f,1.7f });
}

void GameOverScreen::DrawButton(GameInstance* gameInstance, const bool& hoverState)const
{
	int xCoord = ((buttonPos.x + buttonSize.x) - gameInstance->GetTextSize(MenuButtonText).x) / 2;
	if (hoverState)
	{
		gameInstance->FillRect(buttonPos, buttonSize, HoverButtonColour);
		gameInstance->DrawStringDecal(olc::vi2d{ xCoord + 100,buttonPos.y + (buttonSize.y / 2) }, MenuButtonText, olc::WHITE, olc::vf2d{ 1.0f,1.0f });

	}
	else
	{
		gameInstance->FillRect(buttonPos, buttonSize, DefaultButtonColour);
		gameInstance->DrawStringDecal(olc::vi2d{ xCoord + 100,buttonPos.y + (buttonSize.y / 2) }, MenuButtonText, olc::BLACK, olc::vf2d{ 1.0f,1.0f });
	}
}

void GameOverScreen::InitScreen(GameInstance* gameInstance)
{
}

const bool& GameOverScreen::IsMouseHovering()const
{
	return mousePos.x > buttonPos.x && mousePos.x < (buttonPos.x + buttonSize.x) &&
		mousePos.y > buttonPos.y && mousePos.y < (buttonPos.y + buttonSize.y);
}

void GameOverScreen::OnMouseButtonClicked(GameInstance* gameInstance, const bool& bMouseHoverstatus)const
{
	if (!bMouseHoverstatus) { return; }

	if (gameInstance->GetMouse(0).bPressed) { gameInstance->SwitchScreen(gameInstance->GetMenuLevel()); }
}
