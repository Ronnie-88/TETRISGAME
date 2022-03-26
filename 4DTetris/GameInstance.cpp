// 4DTetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "FileReader.h"
#include "Tetramino.h"
#include <iostream>


#define SCREEN_WIDTH 500
#define SCREEN_HIEGHT 415

class GameInstance: public olc::PixelGameEngine
{
    int* Grid;
    int Cleared = 0;
    Tetramino* tetraminoCurrentblock = nullptr;
    //bool flag = true;
   // void(GameInstance::*GameInstanceFuncPtr)();

    olc::Sprite* sprTile;
    olc::Decal* TetrisBlockDecal;
    olc::vi2d vTetrisBlockSize = {7,7};
    olc::vi2d vGridPos = {20,0};
    int gridWidth = 15;
    int gridHeight = 35;
    std::string blockTypes[5] = {"I-Block.txt","L-Block.txt", "O-Block.txt ", "Z-Block.txt","T-Block.txt"};

public:
    GameInstance()
    {
        sAppName = "Not Tetris";
    }
    ~ GameInstance()
    {
        //call delete screens
        print();
        delete[] Grid;
        delete sprTile;
        delete TetrisBlockDecal;
        if (tetraminoCurrentblock)
        {
          delete tetraminoCurrentblock;
        }
        
        std::cout << "GameClosed" << std::endl;
    }
public:

    void drawGrid(int* arr, int gridSizeX, int gridSizeY)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int x = 0; x < gridSizeX; x++)
            {
                if (y < 10)
                {
                    continue;
                }
                switch (arr[y * gridSizeX + x])
                {
                case 0:
                    break;
                case 1:
                    DrawDecal(olc::vi2d(vGridPos.x+x, vGridPos.y+y) * vTetrisBlockSize, TetrisBlockDecal, { 0.025f,0.025f }, olc::GREEN);
                    break;
                case 10:
                    DrawDecal(olc::vi2d(vGridPos.x + x, vGridPos.y + y)*vTetrisBlockSize, TetrisBlockDecal, {0.025f,0.025f}, olc::BLACK);
                    break;
                }

            }
        }
    }
    void CreateNewBlock()
    {
        int randomTetramino = rand() % 5;
        
        if (randomTetramino > 5)
        {
            randomTetramino = 0;
        }

        if (tetraminoCurrentblock && tetraminoCurrentblock->isLanded)
        {
            ClearALLFullRows();
            delete tetraminoCurrentblock;
            tetraminoCurrentblock = new Tetramino(blockTypes[randomTetramino], { (vGridPos.x + gridWidth / 2),0 }, { (gridWidth / 2),0 });
        }
    }

    void ClearALLFullRows()
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
                Cleared++;
                ClearRow(y);
            }
            else if (Cleared > 0)
            {
                MoveDown(y, Cleared);     
            }
        }
        Cleared = 0;
    }
    bool IsRowEmpty(const int& currentRow)
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
    void ClearRow(const int& currentRow)
    {
        for (int x = 1; x < gridWidth-1; x++)
        {
            Grid[currentRow * gridWidth + x] = 0;
        }
    }

    void MoveDown(const int& currentRow,const int& numOfRowsCleared)
    {
        for (int x = 1; x < gridWidth-1; x++)
        {
            int temp = Grid[currentRow * gridWidth + x];
            Grid[currentRow * gridWidth + x] = Grid[(currentRow + numOfRowsCleared) * gridWidth + x];
            Grid[(currentRow + numOfRowsCleared) * gridWidth + x] = temp;
        }
    }

    bool IsRowFilled(const int& currentRow)
    {
        for (int x = 1; x < gridWidth-1; x++)
        {
            if (Grid[currentRow * (gridWidth)+x] != 1)
            {
                return false;
            }
        }
        return true;
    }
    void DebugPrintRow(const int& row)
    {
        for (int x = 1; x < gridWidth - 1; x++)
        {
            std::cout << "[" << Grid[row * (gridWidth)+x] << "] ";
        }
    }
    void print()
    {
        for (int y = 0;  y < gridHeight;  y++)
        {
            std::cout << "\n";
            for (int x = 0; x < gridWidth; x++)
            {
                std::cout << "[" << Grid[y * gridWidth + x] << "] ";
            }
        }
    }


    bool OnUserCreate() override
    {
        Grid = new int[gridWidth * gridHeight];
        sprTile = new olc::Sprite("TetrisBlock.png");
        TetrisBlockDecal = new olc::Decal(sprTile);
        tetraminoCurrentblock = new Tetramino("Z-Block.txt", { (vGridPos.x + gridWidth / 2),0 }, { (gridWidth / 2),0 });

        for ( int y = 0; y < gridHeight; y++)
        {
            for (int x = 0; x < gridWidth; x++)
            {
                if (x == 0 || x == (gridWidth-1) || (y == (gridHeight-1) && x < (gridWidth - 1)))
                {
                    Grid[y * gridWidth + x] = 10;
                }else
                {
                    Grid[y * gridWidth + x] = 0;
                }
            }
        }
        
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::DARK_CYAN);
       
        drawGrid(Grid, gridWidth, gridHeight);
        if (tetraminoCurrentblock)
        {
            tetraminoCurrentblock->DrawTertramino(this, TetrisBlockDecal);
            tetraminoCurrentblock->MoveTetraminoDown(fElapsedTime, Grid, gridWidth, gridHeight);
            tetraminoCurrentblock->MoveTetraminoLeft(GetKey(olc::LEFT).bPressed, Grid, gridWidth, gridHeight);
            tetraminoCurrentblock->MoveTetraminoRight(GetKey(olc::RIGHT).bPressed, Grid, gridWidth, gridHeight);
            tetraminoCurrentblock->RotateTetraminoRight(GetKey(olc::UP).bPressed,Grid,gridHeight,gridWidth);
            tetraminoCurrentblock->IncreaseTetraminoVerticalVelocity(GetKey(olc::DOWN).bHeld);
            CreateNewBlock();
        }
     
        return true;
    }

   
};


int main()
{
    GameInstance Gi;

    if (Gi.Construct(SCREEN_WIDTH, SCREEN_HIEGHT,2,2))
    {
        Gi.Start();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
