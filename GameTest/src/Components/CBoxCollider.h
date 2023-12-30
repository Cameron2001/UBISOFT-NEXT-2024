#pragma once
#include "../Util/Vectors.h"
struct CBoxCollider
{
    vec2 extents;
    bool isVisible = false;
    bool isTrigger = false;
    CBoxCollider(vec2 boxExtents)
    {
        extents = boxExtents;
    }
};
