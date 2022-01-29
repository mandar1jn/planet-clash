#include "planet.h"
#include "customMath.h"
#include "textures.h"
#include <string.h>

static Planet planets[4];
static Planet defaultPlanets[4] = {
    {30, {30, 30}, {0,0}, 10, false, 0},
    {30, {770, 30}, {0,0}, 7, false, 0},
    {30, {30, 420}, {0,0}, 7, false, 0},
    {30, {770, 420}, {0,0}, 7, false, 0},
};

static int minX = 30;
static int minY = 30;
static int maxX = 770;
static int maxY = 420;

bool dragging = false;
bool initializedPositions = false;
float lastX;
float lastY;

void ClampPlanetPosition(int index)
{
    if(planets[index].position.x < minX)
    {
        planets[index].position.x = minX;
    }
    else if(planets[index].position.x > maxX)
    {
        planets[index].position.x = maxX;
    }
    
    if(planets[index].position.y < minY)
    {
        planets[index].position.y = minY;
    }
    else if(planets[index].position.y > maxY)
    {
        planets[index].position.y = maxY;
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
        planets[i].targetPosition.x = RandomInRange(minX, maxX);
        planets[i].targetPosition.y = RandomInRange(minY, maxY);
        planets[i].textureID = RandomInRange(0, 7);
    }
    
    dragging = false;
    initializedPositions = false;
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
        
        if(planets[i].position.x == planets[i].targetPosition.x && planets[i].position.y == planets[i].targetPosition.y)
        {
            planets[i].targetPosition.x = RandomInRange(minX, maxX);
            planets[i].targetPosition.y = RandomInRange(minY, maxY);
        }
        
        if(!planets[i].isBeingDragged)
        {
            planets[i].position = MoveTowards(planets[i].position, planets[i].targetPosition, planets[i].speed * GetFrameTime() * 10);
        }
        
        ClampPlanetPosition(i);
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