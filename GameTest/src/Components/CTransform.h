#pragma once
#include "../Util/Vectors.h"
struct CTransform
{
    vec2 position;
    float rotation;

    CTransform()
    {
        position = vec2(0,0);
        rotation = 0;
    }
    CTransform(vec2 pos, float rot)
    {
        position = pos;
        rotation = rot;
    }
};
