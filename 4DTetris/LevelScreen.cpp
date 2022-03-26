#include "LevelScreen.h"

LevelScreen::LevelScreen()
{
    int girdSize = gridWidth * gridHeight;
    Grid = new int[girdSize];
    sprTile = new olc::Sprite("TetrisBlock.png");
    TetrisBlockDecal = new olc::Decal(sprTile);
    //tetraminoCurrentblock = new Tetramino("Z-Block.txt", { (vGridPos.x + gridWidth / 2),0 }, { (gridWidth / 2),0 });
}
