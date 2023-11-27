#pragma once
#include "../Util/Vectors.h"
struct CTransform
{
    vec2 position;
    float rotation;

    CTransform();
    CTransform(vec2 position);
};
