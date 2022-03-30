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
	//print();
	delete[] Grid;
	delete sprTile;
	delete TetrisBlockDecal;

	if (tetraminoCurrentblock) { delete tetraminoCurrentblock; }

	std::cout << "LevelClosed" << std::endl;
}



void LevelScreen::UpdateScreen(GameInstance* gameInstance, const float& fElapsedTime)//called in onuserupdate
{
	if (!CanDisplayScreen) { return; }
	DrawLevelGrid(gameInstance);
	CreateNewBlock(gameInstance);
	DrawScoreAndLinesCleared(gameInstance);
	DrawTempTetramino(gameInstance);
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

void LevelScreen::InitScreen(GameInstance* gameInstance)
{
	fCurrentTetraminoDefaultMaxWaitTime = 1.0f;
	fCurrentTetraminoStompWaitTime = 0.1f;
	NumOfTetraminosLanded = 0;
	InitGrid();
	gameInstance->ResetScoreAndLines();
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

void LevelScreen::DrawLevelGrid(GameInstance* gameInstance)const
{
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (y < 3) { continue; }

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

void LevelScreen::CreateNewBlock(GameInstance* gameInstance)
{


	if (tetraminoCurrentblock)
	{
		if (!tetraminoCurrentblock->IsTetraminoLanded()) { return; }
		ClearALLFullRows();
		gameInstance->AddToScore(NumOfClearedRows);
		NumOfClearedRows = 0;
		delete tetraminoCurrentblock;
		DecreaseTetraminoSpeed();
		tetraminoCurrentblock = new Tetramino(blockTypes[randomTetramino], { (vGridPos.x + gridWidth / 2),vGridPos.y }, { (gridWidth / 2),0 },
			fCurrentTetraminoDefaultMaxWaitTime, fCurrentTetraminoStompWaitTime, randomInvertTetramino);
		GetRandomTetramino();
	}
	else
	{
		tetraminoCurrentblock = new Tetramino(blockTypes[randomTetramino], { (vGridPos.x + gridWidth / 2),vGridPos.y }, { (gridWidth / 2),0 },
			fCurrentTetraminoDefaultMaxWaitTime, fCurrentTetraminoStompWaitTime, randomInvertTetramino);
		GetRandomTetramino();
	}
}

void LevelScreen::DrawTempTetramino(GameInstance* gameInstance) const
{
	Tetramino temp = Tetramino(blockTypes[randomTetramino], { (vGridPos.x + gridWidth) + 6,(vGridPos.y + (gridHeight / 2)) + 4 }, { (gridWidth / 2),gridHeight / 2 },
		0.0f, 0.0f, randomInvertTetramino);
	gameInstance->DrawStringDecal(olc::vi2d{ vScoreTextPos.x, vScoreTextPos.y + 85 }, NextText);
	temp.DrawTertramino(gameInstance, TetrisBlockDecal);
}

void LevelScreen::ClearALLFullRows()
{
	for (int y = gridHeight - 2; y >= 0; y--)
	{
		//if empty row then don't check
		if (IsRowEmpty(y)) { continue; }

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
}

const bool& LevelScreen::IsRowEmpty(const int& currentRow) const
{
	for (int x = 1; x < gridWidth - 1; x++)
	{
		if (Grid[currentRow * (gridWidth)+x] != 0) { return false; }
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

const bool& LevelScreen::IsRowFilled(const int& currentRow)const
{
	for (int x = 1; x < gridWidth - 1; x++)
	{
		if (Grid[currentRow * (gridWidth)+x] != 1) { return false; }
	}
	return true;
}

void LevelScreen::TriggerGameOver(GameInstance* gameInstance)const
{
	if (IsRowEmpty(3)) { return; }
	gameInstance->SwitchScreen(gameInstance->GetGameOverLevel());
}

void LevelScreen::DrawScoreAndLinesCleared(GameInstance* gameInstance) const
{
	gameInstance->DrawStringDecal(vScoreTextPos, scoreText + std::to_string(gameInstance->GetCurrentScore()));
	gameInstance->DrawStringDecal(vScoreTextPos + olc::vi2d{ 0,15 }, clearedLinesText + std::to_string(gameInstance->GetNumOfLinesCleared()));
}

void LevelScreen::DecreaseTetraminoSpeed()
{
	if (NumOfTetraminosLanded % 5 != 0) { NumOfTetraminosLanded++; return; }
	NumOfTetraminosLanded = 0;
	if (fCurrentTetraminoDefaultMaxWaitTime >= 0.01f) { fCurrentTetraminoDefaultMaxWaitTime -= 0.01f; }
	if (fCurrentTetraminoStompWaitTime >= 0.001f) { fCurrentTetraminoStompWaitTime -= 0.001f; }
}

void LevelScreen::GetRandomTetramino()
{
	randomTetramino = rand() % 5;
	randomInvertTetramino = rand() % 2;
}

//The following method should be defined for debug purposes only

  //   void LevelScreen::print()
	 //{
		// for (int y = 0;  y < gridHeight;  y++)
		// {
		//	 std::cout << "\n";
		//	 for (int x = 0; x < gridWidth; x++)
		//	 {
		//		 std::cout << "[" << Grid[y * gridWidth + x] << "] ";
		//	 }
		// }
		// std::cout << "\n";
	 //}
