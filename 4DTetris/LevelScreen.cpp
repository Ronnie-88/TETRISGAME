#include "LevelScreen.h"
#include "GameInstance.h"
LevelScreen::LevelScreen()
{
	int girdSize = gridWidth * gridHeight;
	Grid = new int[girdSize];
	sprTile = new olc::Sprite("TetrisBlock.png");
	TetrisBlockDecal = new olc::Decal(sprTile);
}

LevelScreen::~LevelScreen()
{
	print();
	delete[] Grid;
	delete sprTile;
	delete TetrisBlockDecal;
	if (tetraminoCurrentblock)
	{
		delete tetraminoCurrentblock;
	}

	std::cout << "LevelClosed" << std::endl;
}



void LevelScreen::UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)//called in onuserupdate
{
	if (!CanDisplayScreen) { return; }
	DrawLevelGrid(gameInstance);
	CreateNewBlock();
	TriggerGameOver(gameInstance);
	//Handle Tetramino block routines
	if (!tetraminoCurrentblock) { return; }

	tetraminoCurrentblock->DrawTertramino(gameInstance, TetrisBlockDecal);
	tetraminoCurrentblock->MoveTetraminoDown(fElapsedTime, Grid, gridWidth, gridHeight);
	tetraminoCurrentblock->MoveTetraminoLeft(gameInstance->GetKey(olc::LEFT).bPressed, Grid, gridWidth, gridHeight);
	tetraminoCurrentblock->MoveTetraminoRight(gameInstance->GetKey(olc::RIGHT).bPressed, Grid, gridWidth, gridHeight);
	tetraminoCurrentblock->RotateTetraminoRight(gameInstance->GetKey(olc::UP).bPressed, Grid, gridHeight, gridWidth);
	tetraminoCurrentblock->IncreaseTetraminoVerticalVelocity(gameInstance->GetKey(olc::DOWN).bHeld);
}

void LevelScreen::InitScreen()
{
	InitGrid();
}


void LevelScreen::InitGrid()
{
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (x == 0 || x == (gridWidth - 1) || (y == (gridHeight - 1) && x < (gridWidth - 1)))
			{
				Grid[y * gridWidth + x] = 10;
			}
			else
			{
				Grid[y * gridWidth + x] = 0;
			}
		}
	}
}

void LevelScreen::DrawLevelGrid(GameInstance* gameInstance)
{
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (y < 3)
			{
				continue;
			}
			switch (Grid[y * gridWidth + x])
			{
			case 0:
				break;
			case 1:
				gameInstance->DrawDecal(olc::vi2d(vGridPos.x + x, vGridPos.y + y) * vTetrisBlockSize, TetrisBlockDecal, { 0.025f,0.025f }, olc::GREEN);
				break;
			case 10:
				gameInstance->DrawDecal(olc::vi2d(vGridPos.x + x, vGridPos.y + y) * vTetrisBlockSize, TetrisBlockDecal, { 0.025f,0.025f }, olc::BLACK);
				break;
			}

		}
	}
}

void LevelScreen::CreateNewBlock()
{
	int randomTetramino = rand() % 5;

	if (randomTetramino > 5)
	{
		randomTetramino = 0;
	}

	if (tetraminoCurrentblock)
	{
		if (!tetraminoCurrentblock->IsTetraminoLanded()) { return; }
		ClearALLFullRows();
		delete tetraminoCurrentblock;
		tetraminoCurrentblock = new Tetramino(blockTypes[randomTetramino], { (vGridPos.x + gridWidth / 2),vGridPos.y }, { (gridWidth / 2),0 });
	}
	else
	{
		tetraminoCurrentblock = new Tetramino(blockTypes[randomTetramino], { (vGridPos.x + gridWidth / 2),vGridPos.y }, { (gridWidth / 2),0 });
	}
}

void LevelScreen::ClearALLFullRows()
{
	for (int y = gridHeight - 2; y >= 0; y--)
	{
		//if empty row then don't check
		if (IsRowEmpty(y))
		{
			continue;
		}
		if (IsRowFilled(y))
		{
			NumOfClearedRows++;
			ClearRow(y);
		}
		else if (NumOfClearedRows > 0)
		{
			MoveRowsDown(y, NumOfClearedRows);
		}
	}
	NumOfClearedRows = 0;
}

bool LevelScreen::IsRowEmpty(const int& currentRow)
{
	for (int x = 1; x < gridWidth - 1; x++)
	{
		if (Grid[currentRow * (gridWidth)+x] != 0)
		{
			return false;
		}
	}
	return true;
}

void LevelScreen::ClearRow(const int& currentRow)
{
	for (int x = 1; x < gridWidth - 1; x++)
	{
		Grid[currentRow * gridWidth + x] = 0;
	}
}

void LevelScreen::MoveRowsDown(const int& currentRow, const int& numOfRowsCleared)
{
	for (int x = 1; x < gridWidth - 1; x++)
	{
		int temp = Grid[currentRow * gridWidth + x];
		Grid[currentRow * gridWidth + x] = Grid[(currentRow + numOfRowsCleared) * gridWidth + x];
		Grid[(currentRow + numOfRowsCleared) * gridWidth + x] = temp;
	}
}

bool LevelScreen::IsRowFilled(const int& currentRow)
{
	for (int x = 1; x < gridWidth - 1; x++)
	{
		if (Grid[currentRow * (gridWidth)+x] != 1)
		{
			return false;
		}
	}
	return true;
}

void LevelScreen::TriggerGameOver(GameInstance* gameInstance)
{
	if (IsRowEmpty(3)) {return;}
	gameInstance->SwitchScreen(gameInstance->GetGameOverLevel());
}

//The following methods should be defined for debug purposes only


/* void DebugPrintRow(const int& row)
   {
	   for (int x = 1; x < gridWidth - 1; x++)
	   {
		   std::cout << "[" << Grid[row * (gridWidth)+x] << "] ";
	   }
   }*/


     void LevelScreen::print()
	 {
		 for (int y = 0;  y < gridHeight;  y++)
		 {
			 std::cout << "\n";
			 for (int x = 0; x < gridWidth; x++)
			 {
				 std::cout << "[" << Grid[y * gridWidth + x] << "] ";
			 }
		 }
		 std::cout << "\n";
	 }
