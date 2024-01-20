#pragma once
#include "../Util/Vectors.h"
struct CRender
{
    vec3 OutlineColor;
    vec3 InsideColor;
    CRender(vec3 colorOut = {1.0,1.0,1.0},vec3 colorIn = {1.0,1.0,1.0}):OutlineColor(colorOut),InsideColor(colorIn){}
};
