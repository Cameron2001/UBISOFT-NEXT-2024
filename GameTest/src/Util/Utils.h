#pragma once
#include "Vectors.h"

class Utils
{
public:
    static const float Deg2Rad;
    static const float Rad2Deg;

    static float Sign(float value);
    static float Clamp(float value, float min, float max);

    static float Lerp(float a, float b, float t);
    static vec2 Lerp(vec2 a, vec2 b, float t);

    static float Distance(vec2 a, vec2 b);
    static float Magnitude(vec2 vector);
    
};
