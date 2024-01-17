#include "stdafx.h"
#include "SEnemy.h"

#include "../Components/CDamageEvent.h"
#include "../Components/CHealth.h"

void SEnemy::Update(Scene& scene, float dt)
{
    
}

void SEnemy::ResolveDamage(Scene& scene)
{
    auto damageIDs = scene.reg.GetEntities<CDamageEvent>();
    for (auto damage_id : damageIDs)
    {
        CDamageEvent* damageEvent = scene.reg.GetComponent<CDamageEvent>(damage_id);
        if(scene.reg.HasComponent<CHealth>(damageEvent->target))
        {
            scene.reg.GetComponent<CHealth>(damageEvent->target)->health-=damageEvent->damage;
        }
    }
    scene.reg.ClearEntities<CDamageEvent>();
}
