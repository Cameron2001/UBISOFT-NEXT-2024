#pragma once
#include "../Util/Vectors.h"
struct CBoxCollider
{
    vec2 min;
    vec2 max;
    bool isVisible = false;
    bool isTrigger = false;
    CBoxCollider(vec2 minimum, vec2 maximum)
    {
        min = minimum;
        max = maximum;
    }
    
};
