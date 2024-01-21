//------------------------------------------------------------------------
// CCollisionEvent.h
//------------------------------------------------------------------------
#pragma once
struct CCollisionEvent
{
    Entity entityA;
    Entity entityB;
    vec2 mtv;
    vec2 normal;
    CCollisionEvent(Entity entityA, Entity entityB, vec2 mtv= {0,0},vec2 norm = {0,0}): entityA(entityA), entityB(entityB), mtv(mtv),normal(norm){}
};
