#include "level.h"
#include "raylib.h"
#include "planet.h"
#include "textures.h"
#include "screens.h"
#include <stdio.h>

static double timeLeft = 0;
static int levelNumber = 0;

char* GetLevelName()
{
    switch(levelNumber)
    {
        case 0:
            return "Level 1 - random movement";
            break;
        case 1:
            return "Level 2 - linked planets";
            break;
        case 2:
            return "Level 3 - the bigger the beter";
            break;
        case 3:
            return "Level 4 - speedy planets";
            break;
        case 4:
            return "Level 5 - perfectly balanced, as all things should be";
            break;
        case 5:
            return "Level 6 - linked contrast";
            break;
    }
    return "Could not get name";
}

void DrawLevelName()
{
    DrawText(GetLevelName(), 1, 1, 20, RAYWHITE);
}

int UpdateTimer()
{
    timeLeft -= GetFrameTime();
    
    if(timeLeft <= 0)
    {
        if(SetLevel(levelNumber + 1))
        {
            return 1;
        }
        InitPlanets();
    }
    
    return 0;
}

void DrawTimer()
{
    DrawTexture(GetTimer(), 0, 20, WHITE);
    char str[5];
    snprintf(str, 5, "%f", timeLeft);
    DrawText(str, 32, 28, 20, RAYWHITE);
}

void SetTimer(double time)
{
    timeLeft = time;
}

int SetLevel(int level)
{
    levelNumber = level;
    if(level >= 6)
    {
        success = true;
        return 1;
    }
    return 0;
}

int GetLevelNumber()
{
    return levelNumber;
}