#include "Tetramino.h"

Tetramino::Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos)
    : vCurrentTetraminoPos(vCurrentTetraminoPos)
{
	tetraminoBlockType = new FileReader(blockTypeFile);
    int girdSize = gridNSize * gridNSize;
	tetraminoGrid = new int[girdSize];
	tetraminoBlockType->AddCoordsToBlock(tetraminoGrid, gridNSize * gridNSize);
}

Tetramino::~Tetramino()
{
	delete tetraminoBlockType;
	delete[] tetraminoGrid;
}

void Tetramino::DrawTertramino(olc::PixelGameEngine* gameInstance, olc::Decal* tetrisBlockDecal)
{
    for (int y = 0; y < gridNSize; y++)
    {
        for (int x = 0; x < gridNSize; x++)
        {
            switch (tetraminoGrid[y * gridNSize + x])
            {
            case 0:
                break;
            case 5:
                gameInstance->DrawDecal(olc::vi2d(vCurrentTetraminoPos.x+x, vCurrentTetraminoPos.y + y) * vTetrisBlockSize, tetrisBlockDecal, { 0.025f,0.025f }, olc::CYAN);
                break;
            }

        }
    }
}

const olc::vi2d& Tetramino::GetCurrentTetraminoPos()
{
    return vCurrentTetraminoPos;
}

void Tetramino::MoveTetraminoDown(const float& fElapsedTime)
{
    if (fCurrentWaitTime <= fMaxWaitTime)
    {
        fCurrentWaitTime += fElapsedTime;
    }
    else
    {
        fCurrentWaitTime = 0.0f;
        vCurrentTetraminoPos += vTetraminoVerticalVelocity;
    }
}

void Tetramino::MoveTetraminoLeft(const bool& bButtonStatus)
{
    if (bButtonStatus)
    {
        vCurrentTetraminoPos += vTetraminoHorizontalLeftVelocity;
    }
}

void Tetramino::MoveTetraminoRight(const bool& bButtonStatus)
{
    if (bButtonStatus)
    {
        vCurrentTetraminoPos += vTetraminoHorizontalRightVelocity;
    }
}

void Tetramino::IncreaseTetraminoVerticalVelocity(const bool& bButtonStatus)
{
    if (bButtonStatus)
    {
        fMaxWaitTime = 0.1f;
    }
    else
    {
        fMaxWaitTime = 1.0f;
    }
}

void Tetramino::RotateTetraminoRight(const bool& bButtonStatus)
{
    if (bButtonStatus)
    {
       TransposeTetraminoGrid();
       SwapTetraminoBlocks();
    }
   
}

void Tetramino::TransposeTetraminoGrid()
{
    for (unsigned int i = 0; i < gridNSize; i++)
    {
        for (unsigned int j = 0; j < gridNSize / 2; j++)
        {
            int temp = tetraminoGrid[i * gridNSize + j];
            tetraminoGrid[i * gridNSize + j] = tetraminoGrid[i * gridNSize + (gridNSize - 1 - j)];
            tetraminoGrid[i * gridNSize + (gridNSize - 1 - j)] = temp;
        }
    }
}

void Tetramino::SwapTetraminoBlocks()
{
    for (unsigned int i = 0; i < gridNSize; i++)
    {
        for (unsigned int j = i + 1; j < gridNSize; j++)
        {
            int temp = tetraminoGrid[i * gridNSize + j];
            tetraminoGrid[i * gridNSize + j] = tetraminoGrid[j * gridNSize + i];
            tetraminoGrid[j * gridNSize + i] = temp;
        }
    }
}


