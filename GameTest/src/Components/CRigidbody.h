#pragma once
#include "../Util/Vectors.h"
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    float friction;
    vec2 normal;

    CRigidbody();
};
