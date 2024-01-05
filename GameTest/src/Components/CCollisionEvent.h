#pragma once
struct CCollisionEvent
{
    Entity entityA;
    Entity entityB;
    vec2 mtv;
    CCollisionEvent(Entity a, Entity b, vec2 minimumTranslation = {0,0}): entityA(a), entityB(b), mtv(minimumTranslation){}
};
