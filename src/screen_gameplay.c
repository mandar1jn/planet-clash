/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "planet.h"
#include "customMath.h"
#include "textures.h"
#include "level.h"
#include <string.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

int minX = 30;
int minY = 30;
int maxX = 770;
int maxY = 420;

static Planet planets[4];
static Planet defaultPlanets[4] = {
    {30, {30, 30}, {0,0}, 10, false, 0},
    {30, {770, 30}, {0,0}, 7, false, 0},
    {30, {30, 420}, {0,0}, 7, false, 0},
    {30, {770, 420}, {0,0}, 7, false, 0},
};

void InitPlanets();

bool dragging = false;
bool initializedPositions = false;
float lastX;
float lastY;

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    
    dragging = false;
    initializedPositions = false;
    
    InitPlanets();
    
    levelNumber = 0;
}

void InitPlanets()
{
    memcpy(planets, defaultPlanets, sizeof defaultPlanets);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition.x = RandomInRange(minX, maxX);
        planets[i].targetPosition.y = RandomInRange(minY, maxY);
        planets[i].textureID = RandomInRange(0, 7);
    }
}


// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    
    for(int i = 0; i < 4; i++)
    {
        if(!dragging || planets[i].isBeingDragged)
        {
            {
                
                if (CheckCollisionPointCircle(GetMousePosition(), planets[i].position, planets[i].radius) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    planets[i].isBeingDragged = true;
                    dragging = true;
                    Vector2 pos = GetMousePosition();
                    lastX = pos.x;
                    lastY = pos.y;
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    planets[i].isBeingDragged = false;
                    dragging = false;
                }

                if (dragging)
                {
                    Vector2 tmp = GetMousePosition();
                    planets[i].position.x += tmp.x - lastX;
                    planets[i].position.y += tmp.y - lastY;
                    
                    lastX = tmp.x;
                    lastY = tmp.y;
                }
            }
        }
        
        if(planets[i].position.x == planets[i].targetPosition.x && planets[i].position.y == planets[i].targetPosition.y)
        {
            planets[i].targetPosition.x = RandomInRange(minX, maxX);
            planets[i].targetPosition.y = RandomInRange(minY, maxY);
        }
        
        if(!planets[i].isBeingDragged)
        {
            planets[i].position = MoveTowards(planets[i].position, planets[i].targetPosition, planets[i].speed * GetFrameTime() * 10);
        }
        
        if(planets[i].position.x < 30)
        {
            planets[i].position.x = 30;
        }
        else if(planets[i].position.x > 770)
        {
            planets[i].position.x = 770;
        }
        
        if(planets[i].position.y < 30)
        {
            planets[i].position.y = 30;
        }
        else if(planets[i].position.y > 420)
        {
            planets[i].position.y = 420;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        for(int j = i+1; j < 4; j++)
        {
            if(CheckCollisionCircles(planets[i].position, planets[i].radius, planets[j].position, planets[j].radius))
            {
                finishScreen = 1;
            }
        }
    }

}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    for(int i = 0; i < 4; i++)
    {
        DrawTexturePro(planetTextures[planets[i].textureID], (Rectangle){0, 0, 32, 32}, (Rectangle){0, 0, 60, 60}, (Vector2){-planets[i].position.x + 30, -planets[i].position.y + 30}, 0, WHITE);
    }
    
    DrawText(GetLevelName(), 1, 1, 20, BLACK);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}