#pragma once
#include "../Util/Utils.h"
struct CArm
{
    float rotation;
    float length;
    vec3 color;
    CArm(float armLength):rotation(0.0f),color({1.0f,1.0f,1.0f}),length(armLength){}
};