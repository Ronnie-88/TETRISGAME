#pragma once
#include "GameScreen.h"
class LevelScreen : public GameScreen
{
public:
	LevelScreen();
	~LevelScreen();
	
private:
	int* Grid = nullptr;
	int Cleared = 0;
	olc::Sprite* sprTile = nullptr;
	olc::Decal* TetrisBlockDecal = nullptr;
	olc::vi2d vTetrisBlockSize = { 7,7 };
	olc::vi2d vGridPos = { 20,0 };
	int gridWidth = 15;
	int gridHeight = 35;
	Tetramino* tetraminoCurrentblock = nullptr;
	std::string blockTypes[5] = { "I-Block.txt","L-Block.txt", "O-Block.txt ", "Z-Block.txt","T-Block.txt" };

public:
	void drawLevelGrid(int* arr, int gridSizeX, int gridSizeY);
	void CreateNewBlock();
	void ClearALLFullRows();
	bool IsRowEmpty(const int& currentRow);
	void ClearRow(const int& currentRow);
	void MoveRowsDown(const int& currentRow, const int& numOfRowsCleared);
	bool IsRowFilled(const int& currentRow);
};

