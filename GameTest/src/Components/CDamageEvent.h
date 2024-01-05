#pragma once
struct CDamageEvent
{
    float damage;
    Entity target;
    CDamageEvent(Entity trgt, float dmg):target(trgt), damage(dmg){}
};