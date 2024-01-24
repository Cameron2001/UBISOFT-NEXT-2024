//------------------------------------------------------------------------
// CRigidbody.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Util/Vectors.h"

//------------------------------------------------------------------------
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    float drag;
    //Used to scale collision projection
    float elasticity;

    CRigidbody(
        const float drag = 0.8f,
        const float elasticity = 1.0f
    ):
        velocity({0.0f, 0.0f}),
        acceleration({0.0f, 0.0f}),
        drag(drag),
        elasticity(elasticity)
    {
    }
};
