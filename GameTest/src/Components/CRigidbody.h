#pragma once
#include "../Util/Vectors.h"
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    float drag;
    
    CRigidbody(float d = 0.8):velocity({0,0}),acceleration({0,0}), drag(d){}
};
