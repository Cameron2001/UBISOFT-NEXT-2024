﻿//------------------------------------------------------------------------
// CRender.h
//------------------------------------------------------------------------
#pragma once
#include "../Util/Vectors.h"
struct CRender
{
    vec3 color;
    CRender(vec3 color = {1.0,1.0,1.0}):color(color){}
};
