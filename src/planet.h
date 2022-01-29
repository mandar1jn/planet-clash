#include "raylib.h"

typedef struct Planet {
    int radius;
    Vector2 position;
    Vector2 targetPosition;
    int speed;
    bool isBeingDragged;
    int textureID;
} Planet;

void ClampPlanetPosition(int index);

void DrawPlanets();

void InitPlanets();

void HandlePlanetDragging();

int CheckPlanetCollision();