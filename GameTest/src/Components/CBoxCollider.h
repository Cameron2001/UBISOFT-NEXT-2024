#pragma once
#include "../Util/Vectors.h"
struct CBoxCollider
{
    vec2 extents;
    vec2 offset;
    bool isTrigger = false;
    CBoxCollider(vec2 boxExtents,vec2 offset = {0.0f,0.0f}): extents(boxExtents), offset(offset){}
};
