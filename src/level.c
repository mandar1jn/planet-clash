#include "level.h"
#include "raylib.h"

char* GetLevelName()
{
    switch(levelNumber)
    {
        case 0:
            return "Level 1 - random movement";
            break;
    }
    return "Could not get name";
}

void DrawLevelName()
{
    DrawText(GetLevelName(), 1, 1, 20, BLACK);
}