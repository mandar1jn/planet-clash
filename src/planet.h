#include "raylib.h"

typedef struct Planet {
    Color color;
    int radius;
    Vector2 position;
    Vector2 targetPosition;
    int speed;
    bool isBeingDragged;
    Texture2D texture;
} Planet;