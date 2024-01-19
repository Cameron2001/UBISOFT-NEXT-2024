#pragma once
#include "../Util/Vectors.h"
struct CRender
{
    bool isUI = false;
    vec3 Color;
    CRender(vec3 color = {1.0,1.0,1.0}, bool ui = false):isUI(ui),Color(color){}
};
