#include "stdafx.h"
#include "SEnemy.h"

#include "../Components/CDamageEvent.h"
#include "../Components/CHealth.h"

void SEnemy::Update(Scene& scene, float dt)
{
    
}

void SEnemy::ResolveDamage(Scene& scene)
{
    for (auto damage_id : scene.reg.GetEntities<CDamageEvent>())
    {
        CDamageEvent* damageEvent = scene.reg.GetComponent<CDamageEvent>(damage_id);
        if(scene.reg.HasComponent<CHealth>(damageEvent->target))
        {
            scene.reg.GetComponent<CHealth>(damageEvent->target)->health-=damageEvent->damage;
        }
    }
    scene.reg.ClearEntities<CDamageEvent>();
}
