#pragma once
#include "../Util/Vectors.h"
struct CLabel
{
    std::string labelText;
    vec2 labelOffset;
    CLabel(std::string myText = "Label",vec2 offset = {0,0}): labelText(myText),labelOffset(offset){}
};
