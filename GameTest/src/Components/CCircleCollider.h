#pragma once
#include "../Util/Vectors.h"
struct CCircleCollider
{
    float radius;
    vec2 normal;
    bool isTrigger = false;
};
