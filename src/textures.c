#include "textures.h"

static Texture2D planetTextures[17];

static Texture2D background;

static Texture2D logo;

static Texture2D timer;

static char* texturePaths[17] = {
    "./resources/Earth.png",
    "./resources/Jupiter.png",
    "./resources/Mars.png",
    "./resources/Mercury.png",
    "./resources/Neptune.png",
    "./resources/Saturn.png",
    "./resources/Uranus.png",
    "./resources/Venus.png",
    "./resources/Blue planet1.png",
    "./resources/orange planet1.png",
    "./resources/B.png",
    "./resources/C.png",
    "./resources/D.png",
    "./resources/E.png",
    "./resources/F.png",
    "./resources/G.png",
    "./resources/H.png",
};

void LoadGameTextures()
{
    for(int i = 0; i < 17; i++)
    {
        planetTextures[i] = LoadTexture(texturePaths[i]);
    }
    
    background = LoadTexture("./resources/background.png");
    logo = LoadTexture("./resources/logo.png");
    timer = LoadTexture("./resources/timer.png");
}

void UnloadGameTextures()
{
    for(int i = 0; i < 17; i++)
    {
        UnloadTexture(planetTextures[i]);
    }
    
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(timer);
}

Texture2D GetPlanetTexture(int index)
{
    return planetTextures[index];
}

void DrawBackground()
{
    DrawTexture(background, 0, 0, WHITE);
}

Texture2D GetLogo()
{
    return logo;
}

Texture2D GetTimer()
{
    return timer;
}