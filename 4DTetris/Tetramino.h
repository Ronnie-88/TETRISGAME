#pragma once
#include "FileReader.h"
#include "olcPixelGameEngine.h"

class Tetramino
{
public:
	Tetramino(const std::string& blockTypeFile, const olc::vi2d& vCurrentTetraminoPos);
	~Tetramino();
	void DrawTertramino(olc::PixelGameEngine* gameInstance , olc::Decal* tetrisBlockDecal);
	const olc::vi2d& GetCurrentTetraminoPos();
	void MoveTetraminoDown();
private:
	olc::vi2d vCurrentTetraminoPos;
	FileReader* tetraminoBlockType = nullptr;
	int* tetraminoGrid = nullptr;
	const unsigned int gridNSize = 5;
	olc::vi2d vTetrisBlockSize = { 7,7 };
};

