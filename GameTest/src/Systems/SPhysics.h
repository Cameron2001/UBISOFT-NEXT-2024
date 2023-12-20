#pragma once
#include "ISystem.h"
#include "../Components/CPlayer.h"
#include "../Components/CRigidbody.h"
#include "../Components/CTransform.h"
#include "../Components/CRender.h"
#include "../Core/Scene.h"
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
