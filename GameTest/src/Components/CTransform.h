#pragma once
#include "../Util/Vectors.h"
struct CTransform
{
    vec2 pos;
    float rot;
    
    CTransform(vec2 position = {0,0}, float rotation =0): pos(position), rot(rotation){}
};
