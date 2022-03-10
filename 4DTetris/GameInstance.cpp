// 4DTetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "FileReader.h"
#include <iostream>


#define BOARD_WIDTH 500
#define BOARD_HIEGHT 415

class GameInstance: public olc::PixelGameEngine
{
    int* Grid;
    int* IBlock;
    
    FileReader* IBlockfileReader = nullptr;

    olc::Sprite* sprTile;
    olc::Decal* TetrisBlockDecal;
    olc::vi2d vTetrisBlockSize = {7,7};
    const olc::vi2d ScreenSize = {512, 415};

public:
    GameInstance()
    {
        sAppName = "Not Tetris";
    }
    ~ GameInstance()
    {
        delete[] Grid;
        delete[] IBlock;
        delete sprTile;
        delete TetrisBlockDecal;
        delete IBlockfileReader;
        std::cout << "GameClosed" << std::endl;
    }
public:

    void drawGrid(int* arr, int gridSize)
    {
        for (int y = 0; y < gridSize; y++)
        {
            for (int x = 0; x < gridSize; x++)
            {
                switch (arr[y * gridSize + x])
                {
                case 0:
                    break;
                case 10:
                    DrawDecal(olc::vi2d(x, y) * vTetrisBlockSize, TetrisBlockDecal, { 0.025f,0.025f }, olc::BLACK);
                    break;
                }

            }
        }
    }
    void drawTetramino(int* arr, int N, int offset)
    {
        for (int y = 0; y < N; y++)
        {
            for (int x = 0;  x < N; x++)
            {
                switch (arr[y * N + x])
                {
                case 0:
                    break;
                case 5:
                    DrawDecal(olc::vi2d(x + offset, y) * vTetrisBlockSize, TetrisBlockDecal, { 0.025f,0.025f });
                    break;
                }
                
            }
        }
    }
    void RotateRightTetramino(int* blockArr, int arraySize)
    {
        int N = (int)sqrt(arraySize);

        for (unsigned int i = 0; i < N; i++)
        {
            for(unsigned int j = i+1; j < N; j++)
            {
                int temp = blockArr[i * N + j];
                blockArr[i * N + j] = blockArr[j * N + i];
                blockArr[j * N + i] = temp;
            }
        }

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N/2; j++)
            {
                int temp = blockArr[i * N + j];
                blockArr[i * N + j] = blockArr[i * N + (N - 1 - j)];
                blockArr[i * N + (N - 1 - j)] = temp;
            }
        }

    }

    void RotateLeftTetramino(int* blockArr, int arraySize)
    {
        int N = (int)sqrt(arraySize);
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N / 2; j++)
            {
                int temp = blockArr[i * N + j];
                blockArr[i * N + j] = blockArr[i * N + (N - 1 - j)];
                blockArr[i * N + (N - 1 - j)] = temp;
            }
        }

        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = i + 1; j < N; j++)
            {
                int temp = blockArr[i * N + j];
                blockArr[i * N + j] = blockArr[j * N + i];
                blockArr[j * N + i] = temp;
            }
        }
    }

    void MoveBlockDown()
    {
    }

    bool OnUserCreate() override
    {
        Grid = new int[50 * 50];
        IBlock = new int[5 * 5];
    
        IBlockfileReader = new FileReader("I-Block.txt");
        sprTile = new olc::Sprite("TetrisBlock.png");
        TetrisBlockDecal = new olc::Decal(sprTile);
        for ( int y = 0; y < 50; y++)
        {
            for (int x = 0; x < 50; x++)
            {
                if (x == 20 || x == 49 || (y == 49 && x > 20))
                {
                    Grid[y * 50 + x] = 10;
                }else
                {
                    Grid[y * 50 + x] = 0;
                }
            }
        }

        IBlockfileReader->AddCoordsToBlock(IBlock, 5 * 5); 
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::DARK_CYAN);
        drawGrid(Grid, 50);
        drawTetramino(IBlock, 5, 25); 

        if (GetKey(olc::D).bPressed)
        {
            RotateRightTetramino(IBlock, 5 * 5);
        }

        if (GetKey(olc::A).bPressed)
        {
            RotateLeftTetramino(IBlock, 5 * 5);
        }
        return true;
    }

   
};


int main()
{
    GameInstance Gi;

    if (Gi.Construct(BOARD_WIDTH, BOARD_HIEGHT,2,2))
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
