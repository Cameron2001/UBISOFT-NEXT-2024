#pragma once
struct CCollisionEvent
{
    Entity entityA;
    Entity entityB;
    vec2 mtv;
    vec2 normal;
    CCollisionEvent(Entity a, Entity b, vec2 minimumTranslation = {0,0},vec2 norm = {0,0}): entityA(a), entityB(b), mtv(minimumTranslation),normal(norm){}
};
