﻿#pragma once
#include "../Components/CRigidbody.h"
#include "../Util/Vectors.h"

class SPhysics
{
public:
    void UpdateCollision();
    void ResolveCollision();
    void CollisionResponse();
    void UpdatePosition();
private:
    //create an array of current collisions
    void addImpulse(vec2 direction, CRigidbody body);
    bool IsColliding();
};
