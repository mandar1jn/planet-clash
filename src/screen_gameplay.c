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
#include <string.h>
#include <math.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

int minX = 25;
int minY = 25;
int maxX = 775;
int maxY = 425;

static Planet planets[4];
static Planet defaultPlanets[4] = {
    {RED, 25, {25, 25}, {0,0}, 10, false},
    {GREEN, 25, {775, 25}, {0,0}, 7, false},
    {BLACK, 25, {25, 425}, {0,0}, 7, false},
    {RED, 25, {775, 425}, {0,0}, 7, false},
};

Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistance)
{
    float xVector = target.x - current.x;
    float yVector = target.y - current.y;
    
    float sqDist = xVector * xVector + yVector * yVector;
    
    if (sqDist == 0 || (maxDistance >= 0 && sqDist <= maxDistance * maxDistance))   
    {
        return target;
    }
    
    float dist = sqrtf(sqDist);
    
    return (Vector2){current.x + xVector / dist * maxDistance, current.y + yVector / dist * maxDistance};
}

int RandomInRange(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void InitPlanets()
{
    memcpy(planets, defaultPlanets, sizeof defaultPlanets);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition.x = RandomInRange(minX, maxX);
        planets[i].targetPosition.y = RandomInRange(minY, maxY);
    }
}

bool dragging = false;
bool isBeingFingerDragged = false;
bool initializedFingers = false;
int lastX;
int lastY;

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    
    dragging = false;
    isBeingFingerDragged = false;
    initializedFingers = false;
    
    InitPlanets();
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
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    planets[i].isBeingDragged = false;
                    dragging = false;
                    isBeingFingerDragged = false;
                }

                if (dragging)
                {
                    Vector2 tmp = GetMouseDelta();
                    planets[i].position.x += tmp.x;
                    planets[i].position.y += tmp.y;
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
        
        if(planets[i].position.x < 25)
        {
            planets[i].position.x = 25;
        }
        else if(planets[i].position.x > 775)
        {
            planets[i].position.x = 775;
        }
        
        if(planets[i].position.y < 25)
        {
            planets[i].position.y = 25;
        }
        else if(planets[i].position.y > 425)
        {
            planets[i].position.y = 425;
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
        DrawCircleV(planets[i].position, planets[i].radius, planets[i].color);
    }
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