#include "level.h"
#include "raylib.h"
#include "planet.h"
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
    }
    return "Could not get name";
}

void DrawLevelName()
{
    DrawText(GetLevelName(), 1, 1, 20, RAYWHITE);
}

void UpdateTimer()
{
    timeLeft -= GetFrameTime();
    
    if(timeLeft <= 0)
    {
        levelNumber += 1;
        InitPlanets();
    }
}

void DrawTimer()
{
    char str[5];
    snprintf(str, 5, "%f", timeLeft);
    DrawText(str, 0, 50, 20, RAYWHITE);
}

void SetTimer(double time)
{
    timeLeft = time;
}

void SetLevel(int level)
{
    levelNumber = level;
}

int GetLevelNumber()
{
    return levelNumber;
}