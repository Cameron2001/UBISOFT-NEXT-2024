#pragma once
#include "../Util/Vectors.h"
struct CRender
{
    vec3 OutlineColor = {1.0,1.0,1.0};
    CRender(vec3 Outline = {1.0,1.0,1.0}):OutlineColor(Outline){}
};
