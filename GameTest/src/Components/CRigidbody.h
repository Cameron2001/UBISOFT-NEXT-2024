//------------------------------------------------------------------------
// CRigidbody.h
//------------------------------------------------------------------------
#pragma once
#include "../Util/Vectors.h"
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    float drag;
    float elasticity;
    CRigidbody(float drag = 0.8f, float elasticity = 1.0f):velocity({0,0}),acceleration({0,0}), drag(drag), elasticity(elasticity){}
};
