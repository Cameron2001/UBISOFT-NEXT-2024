#pragma once
#include "../Util/Vectors.h"
struct CBoxCollider
{
    vec2 min;
    vec2 max;
    vec2 normal;
    bool visible = false;
    bool isTrigger = false;
    CBoxCollider(vec2 minimum, vec2 maximum)
    {
        min = minimum;
        max = maximum;
    }
    
};
