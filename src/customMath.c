#include "customMath.h"
#include <math.h>
#include <stdlib.h>

Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistance)
{
    float xVector = target.x - current.x;
    float yVector = target.y - current.y;
    
    float sqDist = xVector * xVector + yVector * yVector;
    
    if (sqDist == 0 || (maxDistance >= 0 && sqDist <= maxDistance * maxDistance))   
    {
        return target;
    }
    
    float dist = sqrtf(sqDist);
    
    return (Vector2){current.x + xVector / dist * maxDistance, current.y + yVector / dist * maxDistance};
}

int RandomInRange(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int ClampWithOverflow(int orig, int min, int max)
{
    if(orig < min)
    {
        orig = min;
    }
    
    while(orig > max)
    {
        orig -= max + 1;
    }
    
    return orig;
}