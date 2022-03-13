#include "Tetramino.h"

Tetramino::Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos)
    : vCurrentTetraminoPos(vCurrentTetraminoPos)
{
	tetraminoBlockType = new FileReader(blockTypeFile);
	tetraminoGrid = new int[gridNSize * gridNSize];
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
                gameInstance->DrawDecal(olc::vi2d(vCurrentTetraminoPos.x+x, vCurrentTetraminoPos.y + y) * vTetrisBlockSize, tetrisBlockDecal, { 0.025f,0.025f });
                break;
            }

        }
    }
}

const olc::vi2d& Tetramino::GetCurrentTetraminoPos()
{
    return vCurrentTetraminoPos;
}

void Tetramino::MoveTetraminoDown()
{
}


