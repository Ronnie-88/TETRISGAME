#pragma once
#include "GameScreen.h"
#include "Tetramino.h"
class LevelScreen : public GameScreen
{
public:
	LevelScreen();
	~LevelScreen() override;
public:
	void UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)override;
	void InitScreen(GameInstance* gameInstance) override;
	void InitGrid();
private:
	void DrawLevelGrid(GameInstance* gameInstance)const;
	void CreateNewBlock(GameInstance* gameInstance);
	void DrawTempTetramino(GameInstance* gameInstance)const;
	void ClearALLFullRows();
	const bool& IsRowEmpty(const int& currentRow)const;
	void ClearRow(const int& currentRow);
	void MoveRowsDown(const int& currentRow, const int& numOfRowsCleared);
	const bool& IsRowFilled(const int& currentRow)const;
	void TriggerGameOver(GameInstance* gameInstance)const;
	void DrawScoreAndLinesCleared(GameInstance* gameInstance)const;
	void DecreaseTetraminoSpeed();
	void GetRandomTetramino();
	void print();
private:
	int* Grid = nullptr;
	int NumOfClearedRows = 0;
	olc::Sprite* sprTile = nullptr;
	olc::Decal* TetrisBlockDecal = nullptr;
	olc::vi2d vTetrisBlockSize = { 7,7 };
	olc::vi2d vGridPos = { 20,-4 };
	const int gridWidth = 15;
	const int gridHeight = 35;
	olc::vi2d vScoreTextPos = { (vGridPos.x + gridWidth) + 250, gridHeight / 2 };
	olc::vf2d vScoreTextSize = { 1.0f,1.0f };
	std::string scoreText = "Score: ";
	std::string clearedLinesText = "Lines: ";
	std::string NextText = "Next: ";
	Tetramino* tetraminoCurrentblock = nullptr;
	std::string blockTypes[5] = { "I-Block.txt","L-Block.txt", "O-Block.txt ", "Z-Block.txt","T-Block.txt" };
	float fCurrentTetraminoDefaultMaxWaitTime = 1.0f;
	float fCurrentTetraminoStompWaitTime = 0.1f;
	int NumOfTetraminosLanded = 0;
	int randomTetramino = 0;
	int randomInvertTetramino = 0;
};

