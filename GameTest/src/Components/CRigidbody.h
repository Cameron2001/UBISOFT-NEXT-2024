#pragma once
#include "../Util/Vectors.h"
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    float drag;
    CRigidbody(vec2 velo = {0,0}, vec2 accel = {0,0}, float d = 0.8):velocity(velo),acceleration(accel), drag(d){}
};
