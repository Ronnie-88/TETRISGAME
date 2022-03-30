/*
THIS APPLICATION USES THE ONELONECODER PIXEL GAME ENGINE
THIS GAME ENGINE WAS CREATED BY A YOUTUBE USER CALLED javidx9 WHOSE CHANNEL CAN BE FOUND IN THE FOLLOWING LINK BELOW:

https://www.youtube.com/c/javidx9
*/


// EntryPoint.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define OLC_PGE_APPLICATION
#include "ScreenDimensions.h"
#include "GameInstance.h"


int main()
{
	GameInstance Gi;

	if (Gi.Construct(SCREEN_WIDTH, SCREEN_HIEGHT, 2, 2))
	{
		Gi.Start();
	}
}

