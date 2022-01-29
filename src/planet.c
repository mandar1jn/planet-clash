#include "planet.h"
#include "customMath.h"
#include "textures.h"
#include "level.h"
#include <string.h>

static Planet planets[4];
static Planet defaultPlanets[4] = {
    {30, {30, 30}, {0,0}, 10, false, 0},
    {30, {770, 30}, {0,0}, 7, false, 0},
    {30, {770, 420}, {0,0}, 7, false, 0},
    {30, {30, 420}, {0,0}, 7, false, 0},
};

static int minX = 30;
static int minY = 30;
static int maxX = 770;
static int maxY = 420;

bool dragging = false;
bool initializedPositions = false;
float lastX;
float lastY;

void ClampPlanetPositions()
{
    for(int i = 0; i < 4; i++)
    {
        if(planets[i].position.x < minX)
        {
            planets[i].position.x = minX;
        }
        else if(planets[i].position.x > maxX)
        {
            planets[i].position.x = maxX;
        }
        
        if(planets[i].position.y < minY)
        {
            planets[i].position.y = minY;
        }
        else if(planets[i].position.y > maxY)
        {
            planets[i].position.y = maxY;
        }
    }
}

void DrawPlanets()
{
    for(int i = 0; i < 4; i++)
    {
        DrawTexturePro(GetPlanetTexture(planets[i].textureID), (Rectangle){0, 0, 32, 32}, (Rectangle){0, 0, 60, 60}, (Vector2){-planets[i].position.x + 30, -planets[i].position.y + 30}, 0, WHITE);
    }
}

void InitPlanets()
{
    memcpy(planets, defaultPlanets, sizeof defaultPlanets);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].textureID = RandomInRange(0, 9);
    }
    
    dragging = false;
    initializedPositions = false;
    
    switch(levelNumber)
    {
        case 0:
            InitializeLevel1();
            break;
        case 1:
            InitializeLevel2();
            break;
    }
}

//NOTE: currently includes all movement
void HandlePlanetDragging()
{
    for(int i = 0; i < 4; i++)
    {
        if(!dragging || planets[i].isBeingDragged)
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
}

int CheckPlanetCollision()
{
    int colliding = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = i+1; j < 4; j++)
        {
            if(CheckCollisionCircles(planets[i].position, planets[i].radius, planets[j].position, planets[j].radius))
            {
                colliding = 1;
            }
        }
    }
    
    return colliding;
}

void HandlePlanetMovement()
{
    switch(levelNumber)
    {
        case 0:
            HandlePlanetMovementLevel1();
            break;
        case 1:
            HandlePlanetMovementLevel2();
            break;
    }
}

void HandlePlanetMovementLevel1()
{
    for(int i = 0; i < 4; i++)
    {
        if(planets[i].position.x == planets[i].targetPosition.x && planets[i].position.y == planets[i].targetPosition.y)
        {
            planets[i].targetPosition.x = RandomInRange(minX, maxX);
            planets[i].targetPosition.y = RandomInRange(minY, maxY);
        }
        
        if(!planets[i].isBeingDragged)
        {
            planets[i].position = MoveTowards(planets[i].position, planets[i].targetPosition, planets[i].speed * GetFrameTime() * 10);
        }
    }
}

void HandlePlanetMovementLevel2()
{
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition = planets[ClampWithOverflow(i + 2, 0, 3)].position;
        
        if(!planets[i].isBeingDragged)
        {
            planets[i].position = MoveTowards(planets[i].position, planets[i].targetPosition, planets[i].speed * GetFrameTime() * 10);
        }
    }
}

void InitializeLevel1()
{
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition.x = RandomInRange(minX, maxX);
        planets[i].targetPosition.y = RandomInRange(minY, maxY);
    }
}

void InitializeLevel2()
{
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition = planets[ClampWithOverflow(i + 2, 0, 3)].position;
    }
}