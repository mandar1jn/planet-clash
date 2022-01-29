static int levelNumber = 0;

char* GetLevelName()
{
    switch(levelNumber)
    {
        case 0:
            return "Level 1 - random movement";
            break;
    }
    return "Could not get name";
}