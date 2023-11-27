#pragma once

class Utils
{
public:
    static const float Deg2Rad;
    static const float Rad2Deg;

    static float Sign(float value);
    static float Clamp(float value, float min, float max);
    
};
