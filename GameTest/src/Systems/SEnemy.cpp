#include "stdafx.h"
#include "SEnemy.h"

#include "../Components/CDamageEvent.h"
#include "../Components/CHealth.h"

void SEnemy::Update(Scene* scene, float dt)
{
    
}

void SEnemy::ResolveDamage(Scene* scene)
{
    auto damageIDs = scene->m_register.GetEntities<CDamageEvent>();
    for (auto damage_id : damageIDs)
    {
        auto damageEvent = scene->m_register.GetComponent<CDamageEvent>(damage_id);
        if(scene->m_register.HasComponent<CHealth>(damageEvent->target))
        {
            scene->m_register.GetComponent<CHealth>(damageEvent->target)->health-=damageEvent->damage;
        }
    }
    scene->m_register.ClearEntities<CDamageEvent>();
}
