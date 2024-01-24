//------------------------------------------------------------------------
// CCollisionEvent.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CCollisionEvent
{
    Entity entityA;
    Entity entityB;
    //Minimum translation vector, used to resolve collision
    vec2 mtv;
    //Collision normal, used to in collision response to find the projection
    vec2 normal;

    CCollisionEvent(
        const Entity entityA,
        const Entity entityB,
        const vec2 mtv = {0.0f, 0.0f},
        const vec2 norm = {0.0f, 0.0f}
    ):
        entityA(entityA),
        entityB(entityB),
        mtv(mtv),
        normal(norm)
    {
    }
};
