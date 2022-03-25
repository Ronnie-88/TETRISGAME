#pragma once
#include "FileReader.h"
#include "olcPixelGameEngine.h"

class Tetramino
{
public://Tetramino construction
	Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos, const olc::vi2d& vCurrentGridPos);
	~Tetramino();

public://Drawing routines
	void DrawTertramino(olc::PixelGameEngine* gameInstance , olc::Decal* tetrisBlockDecal);
	const olc::vi2d& GetCurrentTetraminoPos();

public://Movement routines
	void MoveTetraminoDown(const float& fElapsedTime, int* grid, int gridWidth, int gridHieght);
	void MoveTetraminoLeft(const bool& bButtonStatus, int* grid, int gridWidth, int gridHieght);
	void MoveTetraminoRight(const bool& bButtonStatus, int* grid, int gridWidth, int gridHieght);
	void IncreaseTetraminoVerticalVelocity(const bool& bButtonStatus);
	void RotateTetraminoRight(const bool& bButtonStatus);
	bool DoesBlockFit(const int* grid, int gridheight, int gridwidth, olc::vi2d potentialMoveVelocity);
	bool isLanded = false;

private:
	void TransposeTetraminoGrid();
	void SwapTetraminoBlocks();
	void TetraminoLanded(int* grid, int gridWidth);
	

private:
	olc::vi2d vCurrentTetraminoPos;
	olc::vi2d vCurrentGridPos;
	FileReader* tetraminoBlockType = nullptr;
	int* tetraminoGrid = nullptr;
	const unsigned int gridNSize = 4;
	olc::vi2d vTetrisBlockSize = {7,7};
	float fCurrentWaitTime = 0.0f; 
	float fMaxWaitTime = 1.0f;
	olc::vi2d vTetraminoVerticalVelocity = {0,1};
	olc::vi2d vTetraminoHorizontalLeftVelocity = {-1,0};
	olc::vi2d vTetraminoHorizontalRightVelocity = {1,0};
	
};

