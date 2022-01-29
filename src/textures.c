#include "textures.h"

static Texture2D planetTextures[8];

static Texture2D background;

static Texture2D logo;

static char* texturePaths[8] = {
    "./resources/Earth.png",
    "./resources/Jupiter.png",
    "./resources/Mars.png",
    "./resources/Mercury.png",
    "./resources/Neptune.png",
    "./resources/Saturn.png",
    "./resources/Uranus.png",
    "./resources/Venus.png",
};

void LoadGameTextures()
{
    for(int i = 0; i < 8; i++)
    {
        planetTextures[i] = LoadTexture(texturePaths[i]);
    }
    
    background = LoadTexture("./resources/background.png");
    logo = LoadTexture("./resources/logo.png");
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