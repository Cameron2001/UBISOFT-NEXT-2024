﻿//------------------------------------------------------------------------
// CTransform.h
//------------------------------------------------------------------------
#pragma once
#include "../Util/Vectors.h"
struct CTransform
{
    vec2 pos;
    CTransform(vec2 position = {0,0}): pos(position){}
};
