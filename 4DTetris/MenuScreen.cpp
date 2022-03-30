#include "MenuScreen.h"
#include "GameInstance.h"
#include"ScreenDimensions.h"

MenuScreen::MenuScreen()
{
	buttonPos = { (SCREEN_WIDTH / 2) - 50,200 };
	buttonSize = { 100,50 };
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)
{
	if (!CanDisplayScreen) { return; }
	mousePos.x = (float)gameInstance->GetMouseX();
	mousePos.y = (float)gameInstance->GetMouseY();

	DrawTitleAndCredits(gameInstance);
	DrawButton(gameInstance, IsMouseHovering());
	OnMouseButtonClicked(gameInstance, IsMouseHovering());
}

void MenuScreen::DrawTitleAndCredits(GameInstance* gameInstance) const
{
	int xCoord = (SCREEN_WIDTH - gameInstance->GetTextSize(TitleText).x) / 2;
	int xCorrd2 = (SCREEN_WIDTH - gameInstance->GetTextSize(CreditsText).x) / 2;
	gameInstance->DrawStringDecal(olc::vi2d{ (xCoord - 100),20 }, TitleText, olc::WHITE, olc::vf2d{ 5.0f,10.0f });
	gameInstance->DrawStringDecal(olc::vi2d{ (xCorrd2 + 100),300 }, CreditsText, olc::BLACK, olc::vf2d{ 0.5f,1.0f });
}

void MenuScreen::DrawButton(GameInstance* gameInstance, const bool& hoverState) const
{
	int xCoord = ((buttonPos.x + buttonSize.x) - gameInstance->GetTextSize(StartButtonText).x) / 2;
	if (hoverState)
	{
		gameInstance->FillRect(buttonPos, buttonSize, HoverButtonColour);
		gameInstance->DrawStringDecal(olc::vi2d{ xCoord + 100,((buttonPos.y + buttonSize.y) / 2) + 100 }, StartButtonText, olc::WHITE, olc::vf2d{ 1.0f,1.0f });

	}
	else
	{
		gameInstance->FillRect(buttonPos, buttonSize, DefaultButtonColour);
		gameInstance->DrawStringDecal(olc::vi2d{ xCoord + 100,((buttonPos.y + buttonSize.y) / 2) + 100 }, StartButtonText, olc::BLACK, olc::vf2d{ 1.0f,1.0f });
	}
}

void MenuScreen::InitScreen(GameInstance* gameInstance)
{

}

const bool& MenuScreen::IsMouseHovering()const
{
	return mousePos.x > buttonPos.x && mousePos.x < (buttonPos.x + buttonSize.x) &&
		mousePos.y > buttonPos.y && mousePos.y < (buttonPos.y + buttonSize.y);
}

void MenuScreen::OnMouseButtonClicked(GameInstance* gameInstance, const bool& bMouseHoverstatus)const
{
	if (!bMouseHoverstatus) { return; }

	if (gameInstance->GetMouse(0).bPressed) { gameInstance->SwitchScreen(gameInstance->GetGameLevel()); }
}
