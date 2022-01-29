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

int minX = 30;
int minY = 30;
int maxX = 770;
int maxY = 420;

static Planet planets[4];
static Planet defaultPlanets[4] = {
    {RED, 30, {30, 30}, {0,0}, 10, false, 0},
    {GREEN, 30, {770, 30}, {0,0}, 7, false, 0},
    {BLACK, 30, {30, 420}, {0,0}, 7, false, 0},
    {RED, 30, {770, 420}, {0,0}, 7, false, 0},
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

void InitPlanets();

bool dragging = false;
bool initializedPositions = false;
int lastX;
int lastY;

double startTime;

static Texture2D planetTextures[8];

char* texturePaths[8] = {
    "./resources/Earth.png",
    "./resources/Jupiter.png",
    "./resources/Mars.png",
    "./resources/Mercury.png",
    "./resources/Neptune.png",
    "./resources/Saturn.png",
    "./resources/Uranus.png",
    "./resources/Venus.png",
};

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    
    dragging = false;
    initializedPositions = false;
    
    InitPlanets();
    
    startTime = GetTime();
    
    
    for(int i = 0; i < 8; i++)
    {
        planetTextures[i] = LoadTexture(texturePaths[i]);
    }
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
                    initializedPositions = true;
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    planets[i].isBeingDragged = false;
                    dragging = false;
                    initializedPositions = false;
                }

                if (dragging)
                {
                    Vector2 tmp = GetMousePosition();
                    planets[i].position.x += tmp.x - lastX;
                    planets[i].position.y += tmp.y - lastY;
                    Vector2 pos = GetMousePosition();
                    lastX = pos.x;
                    lastY = pos.y;
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
        DrawCircleV(planets[i].position, planets[i].radius, planets[i].color);
        DrawTexturePro(planetTextures[planets[i].textureID], (Rectangle){0, 0, 32, 32}, (Rectangle){0, 0, 60, 60}, (Vector2){-planets[i].position.x + 30, -planets[i].position.y + 30}, 0, WHITE);
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