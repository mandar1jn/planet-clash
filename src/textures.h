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

void InitGameTextures()
{
    for(int i = 0; i < 8; i++)
    {
        planetTextures[i] = LoadTexture(texturePaths[i]);
    }
}