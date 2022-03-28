#pragma once
#include "olcPixelGameEngine.h"
#include "FileReader.h"
class GameInstance;

class Tetramino
{
public://Tetramino construction
	Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos, const olc::vi2d& vCurrentGridPos, 
		float fDefaultMaxWaitTime, float fStompWaitTime,const int& inverseSide);
	~Tetramino();

public://Drawing routines
	void DrawTertramino(GameInstance* gameInstance , olc::Decal* tetrisBlockDecal);
	const olc::vi2d& GetCurrentTetraminoPos();

public://Movement routines
	void MoveTetraminoDown(const float& fElapsedTime, int* grid, int gridWidth, int gridHieght);
	void MoveTetraminoLeft(const bool& bButtonStatus, int* grid, int gridWidth, int gridHieght);
	void MoveTetraminoRight(const bool& bButtonStatus, int* grid, int gridWidth, int gridHieght);
	void IncreaseTetraminoVerticalVelocity(const bool& bButtonStatus);
	void RotateTetraminoRight(const bool& bButtonStatus, int* gameGrid, int gridheight, int gridwidth);
	const bool& IsTetraminoLanded();
private:
	bool DoesBlockFit(const int* currentGrid, const int* gameGrid, int gridheight, int gridwidth, olc::vi2d potentialMoveVelocity);
	bool DoesRotatedBlockFit(const int* gameGrid, int gridheight, int gridwidth);
	void TransposeTetraminoGrid(int* grid);
	void SwapTetraminoBlocks(int* grid);
	void TetraminoLanded(int* grid, int gridWidth);
	void FillTempGrid(int* tempGrid, int* currentGrid);
	

private:
	olc::vi2d vCurrentTetraminoPos;
	olc::vi2d vCurrentGridPos;
	FileReader* tetraminoBlockType = nullptr;
	int* tetraminoGrid = nullptr;
	const unsigned int gridNSize = 4;
	olc::vi2d vTetrisBlockSize = {7,7};
	float fCurrentWaitTime = 0.0f;
	float fMaxWaitTime;
	float fDefaultMaxWaitTime;
	float fStompWaitTime;
	olc::vi2d vTetraminoVerticalVelocity = {0,1};
	olc::vi2d vTetraminoHorizontalLeftVelocity = {-1,0};
	olc::vi2d vTetraminoHorizontalRightVelocity = {1,0};
	bool isLanded = false;
	
};

