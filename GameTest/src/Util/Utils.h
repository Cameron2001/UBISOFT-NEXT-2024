#pragma once
#include "Vectors.h"

class Utils
{
public:
    static const float Deg2Rad;
    static const float Rad2Deg;

    static float Sign(float value);
    static float Clamp(float value, float min, float max);
    static vec2 Clamp(const vec2 vector, const float max_length);
    static float Clamp(float value);

    static float Lerp(float a, float b, float t);
    static vec2 Lerp(vec2 a, vec2 b, float t);
    static float LerpUnclamped(float a, float b, float t);
    static float LerpAngle(float a, float b, float t);
    static float Repeat(float t, float length);

    static float Distance(vec2 a, vec2 b);
    static float SquaredDistance(vec2 a, vec2 b);
    static float Magnitude(vec2 vector);
    static float SquaredMagnitude(vec2 vector);
    static vec2 LimitMagnitude(vec2 vector, float magnitude);

    static vec2 Min(vec2 vec_a, vec2 vec_b);
    static float Min(float a, float b);
    static vec2 Max(vec2 vec_a, vec2 vec_b);
    static float Max(float a, float b);
    static vec2 Negate(vec2 vec);
    static vec2 Inverse(vec2 vec);
    static vec2 Normalize(vec2 vec);
    static float Angle(vec2 from, vec2 to);
    static float Dot(vec2 lhs, vec2 rhs);
    static float SignedAngle(vec2 from, vec2 to);
private:
    Utils();
    ~Utils();
    
};
