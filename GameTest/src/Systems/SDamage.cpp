#include "stdafx.h"
#include "SDamage.h"

#include "../Components/Components.h"

void SDamage::Update(Scene& scene, float dt)
{
    auto damageEvents = scene.reg.GetEntities<CDamageEvent>();
    for (auto damage_event : damageEvents)
    {
        CDamageEvent* event = scene.reg.GetComponent<CDamageEvent>(damage_event);
        CHealth* health = scene.reg.GetComponent<CHealth>(event->target);
        health->health-= event->damage;
        
    }
    
    for (auto health_id : scene.reg.GetEntities<CHealth>())
    {
        CHealth* health = scene.reg.GetComponent<CHealth>(health_id);
        if(health->health<=0)
        {
            scene.reg.AddComponent(health_id,CDeleteMe());
        }
    }
}
