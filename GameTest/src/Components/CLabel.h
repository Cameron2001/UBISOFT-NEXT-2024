#pragma once
#include "../Util/Vectors.h"
struct CLabel
{
    const char* labelText;
    vec2 labelOffset;
    CLabel(const char* myText = "Label",vec2 offset = {0,0}): labelText(myText),labelOffset(offset){}
};
