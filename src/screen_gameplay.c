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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

static Planet planets[6] = {
    {RED, 25, 200, 225, {0,0}, 0, false},
    {GREEN, 25, 300, 225, {0,0}, 0, false},
    {BLACK, 25, 400, 225, {0,0}, 0, false},
    {RED, 25, 500, 225, {0,0}, 0, false},
    {YELLOW, 25, 600, 225, {0,0}, 0, false},
    {PURPLE, 25, 700, 225, {0,0}, 0, false},
};

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
}

bool dragging = false;



// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    
    for(int i = 0; i < 6; i++)
    {
        if(!dragging ||planets[i].isBeingDragged)
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
            }

            if (dragging)
            {
                Vector2 tmp = GetMouseDelta();
                planets[i].position.x += tmp.x;
                planets[i].position.y += tmp.y;
            }
        }
    }

    for(int i = 0; i < 6; i++)
    {
        for(int j = i+1; j < 6; j++)
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
    for(int i = 0; i < 6; i++)
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