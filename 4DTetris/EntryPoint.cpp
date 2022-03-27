
// EntryPoint.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define OLC_PGE_APPLICATION
#include "GameInstance.h"
#define SCREEN_WIDTH 500
#define SCREEN_HIEGHT 415

int main()
{
    GameInstance Gi;

    if (Gi.Construct(SCREEN_WIDTH, SCREEN_HIEGHT,2,2))
    {
        Gi.Start();
    }
}

