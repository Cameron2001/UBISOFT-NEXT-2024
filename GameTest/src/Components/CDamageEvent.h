//------------------------------------------------------------------------
// CDamageEvent.h
//------------------------------------------------------------------------
#pragma once
struct CDamageEvent
{
    float damage;
    Entity target;
    CDamageEvent(Entity target, float damage):target(target), damage(damage){}
};