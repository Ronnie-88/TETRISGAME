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
 
    Tetramino* tetraminoIblock = nullptr;

    olc::Sprite* sprTile;
    olc::Decal* TetrisBlockDecal;
    olc::vi2d vTetrisBlockSize = {7,7};
    olc::vi2d vGridPos = {20,0};
    int gridWidth = 29;
    int gridHeight = 50;

public:
    GameInstance()
    {
        sAppName = "Not Tetris";
    }
    ~ GameInstance()
    {
        delete[] Grid;
        delete sprTile;
        delete TetrisBlockDecal;
        delete tetraminoIblock;
        std::cout << "GameClosed" << std::endl;
    }
public:

    void drawGrid(int* arr, int gridSizeX, int gridSizeY)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int x = 0; x < gridSizeX; x++)
            {
                switch (arr[y * gridSizeX + x])
                {
                case 0:
                    break;
                case 1:
                    DrawDecal(olc::vi2d(vGridPos.x+x, vGridPos.y+y) * vTetrisBlockSize, TetrisBlockDecal, { 0.025f,0.025f });
                case 10:
                    DrawDecal(olc::vi2d(vGridPos.x + x, vGridPos.y + y)*vTetrisBlockSize, TetrisBlockDecal, {0.025f,0.025f}, olc::BLACK);
                    break;
                }

            }
        }
    }



    bool OnUserCreate() override
    {
        Grid = new int[gridWidth * gridHeight];
    
        sprTile = new olc::Sprite("TetrisBlock.png");
        TetrisBlockDecal = new olc::Decal(sprTile);
        tetraminoIblock = new Tetramino("I-Block.txt", { (vGridPos.x + gridWidth / 2),0 }, { (gridWidth / 2),0 });

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
        
        tetraminoIblock->DrawTertramino(this, TetrisBlockDecal);
        tetraminoIblock->MoveTetraminoDown(fElapsedTime,Grid, gridWidth, gridHeight);
        tetraminoIblock->MoveTetraminoLeft(GetKey(olc::LEFT).bPressed,Grid,gridWidth,gridHeight);
        tetraminoIblock->MoveTetraminoRight(GetKey(olc::RIGHT).bPressed,Grid, gridWidth, gridHeight);
        tetraminoIblock->RotateTetraminoRight(GetKey(olc::UP).bPressed);
        tetraminoIblock->IncreaseTetraminoVerticalVelocity(GetKey(olc::DOWN).bHeld);
        
     
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
