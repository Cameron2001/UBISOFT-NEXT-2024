#pragma once
#include "Vectors.h"

class Utils
{
public:
    static const float Deg2Rad;
    static const float Rad2Deg;

    static float Sign(float value);
    static float Clamp(float value, float min, float max);
    static vec2 Clamp(vec2 vector,float max_length);
    static float Clamp(float value);

    static float Lerp(float a, float b, float t);
    static vec2 Lerp(vec2 a, vec2 b, float t);

    static float Distance(vec2 a, vec2 b);
    static float SquaredDistance(vec2 a, vec2 b);
    static float Magnitude(vec2 vector);
    static float SquaredMagnitude(vec2 vector);

    static float Length(vec2 vec);
    static float LengthSquared(vec2 vec);
    static vec2 Normalize(vec2 vec);
    static float Dot(vec2 lhs, vec2 rhs);
    static vec2 Project(vec2 a,vec2 b);
private:
    Utils();
    ~Utils();
    
};
