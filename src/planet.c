#include "planet.h"
#include "customMath.h"
#include "textures.h"
#include "level.h"
#include <string.h>

static Planet planets[4];
static Planet defaultPlanets[4] = {
    {30, {30, 30}, {0,0}, 7, false, 0},
    {30, {770, 30}, {0,0}, 7, false, 0},
    {30, {770, 420}, {0,0}, 7, false, 0},
    {30, {30, 420}, {0,0}, 7, false, 0},
};

bool dragging = false;
bool initializedPositions = false;
float lastX;
float lastY;

void ClampPlanetPositions()
{
    for(int i = 0; i < 4; i++)
    {
        if(planets[i].position.x < planets[i].radius)
        {
            planets[i].position.x = planets[i].radius;
        }
        else if(planets[i].position.x > 800 - planets[i].radius)
        {
            planets[i].position.x = 800 - planets[i].radius;
        }
        
        if(planets[i].position.y < planets[i].radius)
        {
            planets[i].position.y = planets[i].radius;
        }
        else if(planets[i].position.y > 450 - planets[i].radius)
        {
            planets[i].position.y = 450 - planets[i].radius;
        }
    }
}

void DrawPlanets()
{
    for(int i = 0; i < 4; i++)
    {
        DrawTexturePro(GetPlanetTexture(planets[i].textureID), (Rectangle){0, 0, 32, 32}, (Rectangle){0, 0, planets[i].radius * 2, planets[i].radius * 2}, (Vector2){-planets[i].position.x + planets[i].radius, -planets[i].position.y + planets[i].radius}, 0, WHITE);
    }
}

void InitPlanets()
{
    memcpy(planets, defaultPlanets, sizeof defaultPlanets);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].textureID = RandomInRange(0, 16);
    }
    
    dragging = false;
    initializedPositions = false;
    
    switch(GetLevelNumber())
    {
        case 0:
            InitializeLevel1();
            break;
        case 1:
            InitializeLevel2();
            break;
        case 2:
            InitializeLevel3();
            break;
        case 3:
            InitializeLevel4();
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
    switch(GetLevelNumber())
    {
        case 0:
            HandlePlanetMovementLevel1();
            break;
        case 1:
            HandlePlanetMovementLevel2();
            break;
        case 2:
            HandlePlanetMovementLevel1();
            break;
        case 3:
            HandlePlanetMovementLevel1();
    }
}

void HandlePlanetMovementLevel1()
{
    for(int i = 0; i < 4; i++)
    {
        if(planets[i].position.x == planets[i].targetPosition.x && planets[i].position.y == planets[i].targetPosition.y)
        {
            planets[i].targetPosition.x = RandomInRange(planets[i].radius, 800 - planets[i].radius);
            planets[i].targetPosition.y = RandomInRange(planets[i].radius, 450 - planets[i].radius);
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
    SetTimer(15);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition.x = RandomInRange(planets[i].radius, 800 - planets[i].radius);
        planets[i].targetPosition.y = RandomInRange(planets[i].radius, 450 - planets[i].radius);
    }
}

void InitializeLevel2()
{
    SetTimer(10);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].targetPosition = planets[ClampWithOverflow(i + 2, 0, 3)].position;
    }
}

void InitializeLevel3()
{
    SetTimer(15);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].radius = 50;
        planets[i].targetPosition.x = RandomInRange(planets[i].radius, 800 - planets[i].radius);
        planets[i].targetPosition.y = RandomInRange(planets[i].radius, 450 - planets[i].radius);
        planets[i].speed = 4;
    }
}

void InitializeLevel4()
{
    SetTimer(15);
    
    for(int i = 0; i < 4; i++)
    {
        planets[i].radius = 20;
        planets[i].targetPosition.x = RandomInRange(planets[i].radius, 800 - planets[i].radius);
        planets[i].targetPosition.y = RandomInRange(planets[i].radius, 450 - planets[i].radius);
        planets[i].speed = 13;
    }
}