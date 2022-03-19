#pragma once
#include "FileReader.h"
#include "olcPixelGameEngine.h"

class Tetramino
{
public://Tetramino construction
	Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos);
	~Tetramino();

public://Drawing routines
	void DrawTertramino(olc::PixelGameEngine* gameInstance , olc::Decal* tetrisBlockDecal);
	const olc::vi2d& GetCurrentTetraminoPos();

public://Movement routines
	void MoveTetraminoDown(const float& fElapsedTime);
	void MoveTetraminoLeft(const bool& bButtonStatus);
	void MoveTetraminoRight(const bool& bButtonStatus);
	void IncreaseTetraminoVerticalVelocity(const bool& bButtonStatus);
	void RotateTetraminoRight(const bool& bButtonStatus);
	void DetectSideLeft(int gridWidth, olc::vi2d gridPos);
	void DetectSideRight(int gridWidth, olc::vi2d gridPos);
	void DetectBottom(int gridHeight);


private:
	void TransposeTetraminoGrid();
	void SwapTetraminoBlocks();

private:
	olc::vi2d vCurrentTetraminoPos;
	FileReader* tetraminoBlockType = nullptr;
	int* tetraminoGrid = nullptr;
	const unsigned int gridNSize = 4;
	olc::vi2d vTetrisBlockSize = {7,7};
	float fCurrentWaitTime = 0.0f; 
	float fMaxWaitTime = 1.0f;
	olc::vi2d vTetraminoVerticalVelocity = {0,1};
	olc::vi2d vTetraminoHorizontalLeftVelocity = {-1,0};
	olc::vi2d vTetraminoHorizontalRightVelocity = {1,0};
	bool bCanTetraminoBlockMoveDown = true;
	bool bCanTetraminoBlockMoveLeft = true;
	bool bCanTetraminoBlockMoveRight = true;
};

