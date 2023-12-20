#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"
#include "../Components/CRigidbody.h"
#include "../Util/Vectors.h"

class SPhysics : public ISystem
{
public:
    void Update(Scene* scene);
    void UpdateCollision();
    void ResolveCollision();
    void CollisionResponse();
    void UpdatePosition();
private:
    //create an array of current collisions
    void addImpulse(vec2 direction, CRigidbody body);
    bool IsColliding();
};
