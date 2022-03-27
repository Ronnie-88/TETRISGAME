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
	void InitScreen() override;
	void InitGrid();
private:
	void DrawLevelGrid(GameInstance* gameInstance);
	void CreateNewBlock();
	void ClearALLFullRows();
	bool IsRowEmpty(const int& currentRow);
	void ClearRow(const int& currentRow);
	void MoveRowsDown(const int& currentRow, const int& numOfRowsCleared);
	bool IsRowFilled(const int& currentRow);
	void TriggerGameOver(GameInstance* gameInstance);
	void print();
private:
	int* Grid = nullptr;
	int NumOfClearedRows = 0;
	olc::Sprite* sprTile = nullptr;
	olc::Decal* TetrisBlockDecal = nullptr;
	olc::vi2d vTetrisBlockSize = { 7,7 };
	olc::vi2d vGridPos = { 20,-4 };
	int gridWidth = 15;
	int gridHeight = 35;
	Tetramino* tetraminoCurrentblock = nullptr;
	std::string blockTypes[5] = { "I-Block.txt","L-Block.txt", "O-Block.txt ", "Z-Block.txt","T-Block.txt" };
};

