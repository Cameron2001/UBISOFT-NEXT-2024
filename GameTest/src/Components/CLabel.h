//------------------------------------------------------------------------
// CLabel.h
//------------------------------------------------------------------------
#pragma once
#include "../Util/Vectors.h"
struct CLabel
{
    std::string text;
    vec2 offset;
    CLabel(std::string text = "Label",vec2 offset = {0,0}): text(text),offset(offset){}
};
