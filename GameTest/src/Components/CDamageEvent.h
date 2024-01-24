//------------------------------------------------------------------------
// CDamageEvent.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CDamageEvent
{
    float damage;
    Entity target;

    CDamageEvent(
        const Entity target,
        const float damage
    ):
        damage(damage),
        target(target)
    {
    }
};
