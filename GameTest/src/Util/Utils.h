//------------------------------------------------------------------------
// Utils.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "Vectors.h"
//------------------------------------------------------------------------
class utils
{
public:
    //utility functions
    static const float deg2Rad;
    static const float rad2Deg;

    static float sign(float value);
    static float clamp(float value, float min, float max);
    static vec2 clamp(vec2 vector,float max_length);
    static float clamp(float value);

    static float lerp(float a, float b, float t);
    static vec2 lerp(vec2 a, vec2 b, float t);

    static float distance(vec2 a, vec2 b);
    static float squaredDistance(vec2 a, vec2 b);
    static float magnitude(vec2 vector);
    static float squaredMagnitude(vec2 vector);

    static float length(vec2 vector);
    static float lengthSquared(vec2 vector);
    static vec2 normalize(vec2 vector);
    static float dot(vec2 a, vec2 b);
    static vec2 project(vec2 a, vec2 b);
private:
    utils();
    ~utils();
    
};
