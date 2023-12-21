#pragma once
#include "../Util/Vectors.h"
struct CRigidbody
{
    vec2 velocity;
    vec2 acceleration;
    vec2 normal;
    vec2 force;
    float mass;
    float friction = 0.0f;
    float restitution = 1.0f;
    float invMass = 1.0f;
    float gravityScale = 1.0f;
};
