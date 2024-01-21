#pragma once
#include "../Util/Vectors.h"
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    float drag;
    float elasticity;
    CRigidbody(float d = 0.8f, float e = 1.0f):velocity({0,0}),acceleration({0,0}), drag(d), elasticity(e){}
};
