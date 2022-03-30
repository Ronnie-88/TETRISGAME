#include "Tetramino.h"
#include"GameInstance.h"
Tetramino::Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos, const olc::vi2d& vCurrentGridPos, const float& fDefaultMaxWaitTime, const float& fStompWaitTime, const int& inverseSide)
	: vCurrentTetraminoPos(vCurrentTetraminoPos), vCurrentGridPos(vCurrentGridPos), fDefaultMaxWaitTime(fDefaultMaxWaitTime), fStompWaitTime(fStompWaitTime)
{
	tetraminoBlockType = new FileReader(blockTypeFile);
	int girdSize = gridNSize * gridNSize;
	tetraminoGrid = new int[girdSize];
	tetraminoBlockType->AddCoordsToBlock(tetraminoGrid, gridNSize * gridNSize);
	fMaxWaitTime = this->fDefaultMaxWaitTime;

	if (inverseSide == 1) { SwapTetraminoBlocks(tetraminoGrid); }
}

Tetramino::~Tetramino()
{
	delete tetraminoBlockType;
	delete[] tetraminoGrid;
}

void Tetramino::DrawTertramino(GameInstance* gameInstance, olc::Decal* tetrisBlockDecal)
{
	if (isLanded) { return; }

	for (unsigned int y = 0; y < gridNSize; y++)
	{
		for (unsigned int x = 0; x < gridNSize; x++)
		{
			switch (tetraminoGrid[y * gridNSize + x])
			{
			case 0:
				//gameInstance->DrawDecal(olc::vi2d(vCurrentTetraminoPos.x + x, vCurrentTetraminoPos.y + y) * vTetrisBlockSize, tetrisBlockDecal, { 0.025f,0.025f }, olc::DARK_BLUE);
				break;
			case 5:
				gameInstance->DrawDecal(olc::vi2d(vCurrentTetraminoPos.x + x, vCurrentTetraminoPos.y + y) * vTetrisBlockSize, tetrisBlockDecal, { 0.025f,0.025f }, olc::CYAN);
				break;
			}

		}
	}
}

const olc::vi2d& Tetramino::GetCurrentTetraminoPos()const
{
	return vCurrentTetraminoPos;
}

void Tetramino::MoveTetraminoDown(const float& fElapsedTime, int* grid, const int& gridWidth, const int& gridHieght)
{
	if (isLanded) { return; }

	if (fCurrentWaitTime <= fMaxWaitTime)
	{
		fCurrentWaitTime += fElapsedTime;
	}
	else
	{
		if (!DoesBlockFit(tetraminoGrid, grid, gridHieght, gridWidth, vTetraminoVerticalVelocity))
		{
			TetraminoLanded(grid, gridWidth);
			isLanded = true;
			return;
		}
		fCurrentWaitTime = 0.0f;
		vCurrentTetraminoPos += vTetraminoVerticalVelocity;
		vCurrentGridPos += vTetraminoVerticalVelocity;
	}
}

void Tetramino::MoveTetraminoLeft(const bool& bButtonStatus, int* grid, const int& gridWidth, const int& gridHieght)
{
	if (isLanded) { return; }

	if (bButtonStatus)
	{
		if (!DoesBlockFit(tetraminoGrid, grid, gridHieght, gridWidth, vTetraminoHorizontalLeftVelocity)) { return; }
		vCurrentTetraminoPos += vTetraminoHorizontalLeftVelocity;
		vCurrentGridPos += vTetraminoHorizontalLeftVelocity;
	}
}

void Tetramino::MoveTetraminoRight(const bool& bButtonStatus, int* grid, const int& gridWidth, const int& gridHieght)
{
	if (isLanded) { return; }

	if (bButtonStatus)
	{
		if (!DoesBlockFit(tetraminoGrid, grid, gridHieght, gridWidth, vTetraminoHorizontalRightVelocity)) { return; }
		vCurrentTetraminoPos += vTetraminoHorizontalRightVelocity;
		vCurrentGridPos += vTetraminoHorizontalRightVelocity;
	}
}

void Tetramino::IncreaseTetraminoVerticalVelocity(const bool& bButtonStatus)
{
	if (isLanded) { return; }

	if (bButtonStatus)
	{
		fMaxWaitTime = fStompWaitTime;
	}
	else
	{
		fMaxWaitTime = fDefaultMaxWaitTime;
	}
}

void Tetramino::RotateTetraminoRight(const bool& bButtonStatus, int* gameGrid, const int& gridheight, const int& gridwidth)
{
	if (isLanded) { return; }

	if (
		!(bButtonStatus && DoesRotatedBlockFit(gameGrid, gridheight, gridwidth))
		)
	{
		return;
	}

	TransposeTetraminoGrid(tetraminoGrid);
	SwapTetraminoBlocks(tetraminoGrid);

}

const bool& Tetramino::IsTetraminoLanded() const
{
	return isLanded;
}

const bool& Tetramino::DoesBlockFit(const int* currentGrid, const int* gameGrid, const int& gridheight, const int& gridwidth, const olc::vi2d& potentialMoveVelocity)
{
	olc::vi2d potentialMovePos = { 0,0 };

	//rotate temp and check if it collides
	for (unsigned int y = 0; y < gridNSize; y++)
	{
		for (unsigned int x = 0; x < gridNSize; x++)
		{
			potentialMovePos = vCurrentGridPos + potentialMoveVelocity;
			if (currentGrid[y * gridNSize + x] != 0)
			{
				if ((potentialMovePos.x + x) <= 0)//left side of grid
				{
					canBlockFit = false;
					return canBlockFit;
					//return !canBlockFit;
				}
				if ((potentialMovePos.x + x) > (gridwidth - 2))//right side of grid
				{
					canBlockFit = false;
					return canBlockFit;
					//return !canBlockFit;
				}
				if ((potentialMovePos.y + y) > (gridheight - 2))//base of grid
				{
					canBlockFit = false;
					return canBlockFit;
					//return !canBlockFit;
				}
				if (gameGrid[(potentialMovePos.y + y) * (gridwidth)+(potentialMovePos.x + x)] == 1)//collision with another block
				{
					canBlockFit = false;
					return canBlockFit;
					//return !canBlockFit;
				}
			}
		}
	}
	canBlockFit = true;
	return canBlockFit;
	//return canBlockFit;
}

const bool& Tetramino::DoesRotatedBlockFit(const int* gameGrid, const int& gridheight, const int& gridwidth)
{
	int tempRotatedTetraminoGrid[4 * 4];
	FillTempGrid(tempRotatedTetraminoGrid, tetraminoGrid);
	//rotate temp grid
	TransposeTetraminoGrid(tempRotatedTetraminoGrid);
	SwapTetraminoBlocks(tempRotatedTetraminoGrid);
	if (!DoesBlockFit(tempRotatedTetraminoGrid, gameGrid, gridheight, gridwidth, { 0,0 })) { return !canRotatedBlockFit; }

	return canRotatedBlockFit;
}

void Tetramino::TransposeTetraminoGrid(int* grid)
{
	for (unsigned int i = 0; i < gridNSize; i++)
	{
		for (unsigned int j = 0; j < gridNSize / 2; j++)
		{
			int temp = grid[i * gridNSize + j];
			grid[i * gridNSize + j] = grid[i * gridNSize + (gridNSize - 1 - j)];
			grid[i * gridNSize + (gridNSize - 1 - j)] = temp;
		}
	}
}

void Tetramino::SwapTetraminoBlocks(int* grid)
{
	for (unsigned int i = 0; i < gridNSize; i++)
	{
		for (unsigned int j = i + 1; j < gridNSize; j++)
		{
			int temp = grid[i * gridNSize + j];
			grid[i * gridNSize + j] = grid[j * gridNSize + i];
			grid[j * gridNSize + i] = temp;
		}
	}
}

void Tetramino::TetraminoLanded(int* grid, int gridWidth)
{
	if (isLanded) { return; }

	for (unsigned int y = 0; y < gridNSize; y++)
	{
		for (unsigned int x = 0; x < gridNSize; x++)
		{
			if (tetraminoGrid[y * gridNSize + x] != 0)
			{
				grid[(vCurrentGridPos.y + y) * gridWidth + (vCurrentGridPos.x + x)] = 1;
			}
		}
	}
}

void Tetramino::FillTempGrid(int* tempGrid, int* currentGrid)
{
	for (unsigned int i = 0; i < gridNSize * gridNSize; i++)
	{
		tempGrid[i] = currentGrid[i];
	}
}


