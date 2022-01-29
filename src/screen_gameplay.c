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
    {RED, 30, {25, 25}, {0,0}, 10, false, NULL},
    {GREEN, 30, {775, 25}, {0,0}, 7, false, NULL},
    {BLACK, 30, {25, 425}, {0,0}, 7, false, NULL},
    {RED, 30, {775, 425}, {0,0}, 7, false, NULL},
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

static int baseTakenPlanets = {9, 9, 9, 9, 9, 9, 9};
static int takenPlanets[8] = {9, 9, 9, 9, 9, 9, 9};
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
    
    memcpy(takenPlanets, baseTakenPlanets, sizeof baseTakenPlanets);
    
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
        int textureIndex = RandomInRange(0, 7);
        planets[i].texture = planetTextures[textureIndex];
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
        DrawTexturePro(planets[i].texture, (Rectangle){0, 0, 32, 32}, (Rectangle){0, 0, 60, 60}, (Vector2){-planets[i].position.x + 30, -planets[i].position.y + 30}, 0, WHITE);
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