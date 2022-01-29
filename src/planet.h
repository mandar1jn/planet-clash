#include "raylib.h"

typedef struct Planet {
    int radius;
    Vector2 position;
    Vector2 targetPosition;
    int speed;
    bool isBeingDragged;
    int textureID;
} Planet;

void ClampPlanetPositions();

void DrawPlanets();

void InitPlanets();

void HandlePlanetDragging();

int CheckPlanetCollision();

void HandlePlanetMovement();

void HandlePlanetMovementLevel1();

void HandlePlanetMovementLevel2();

void InitializeLevel1();

void InitializeLevel2();

void InitializeLevel3();

void InitializeLevel4();

void InitializeLevel5();

void InitializeLevel6();