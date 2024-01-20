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
    
    for (const auto health_id : scene.reg.GetEntities<CHealth>())
    {
        const CHealth* health = scene.reg.GetComponent<CHealth>(health_id);
        if(health->health<=0)
        {
            if(scene.reg.HasComponent<CPlayer>(health_id))
            {
                //end game
            }
            else
            {
                scene.reg.DeleteEntity(health_id);
            }
        }
        if(scene.reg.HasComponent<CRender>(health_id))
        {
            CRender* render = scene.reg.GetComponent<CRender>(health_id);
            if (health->health<75)
            {
                render->Color={1.0f,0.0f,0.0f};
            }
            else if(health->health<100)
            {
                render->Color= {1.0f,1.0f,0.0f};
            }
        }
        
    }
    scene.reg.ClearEntities<CDamageEvent>();
}
