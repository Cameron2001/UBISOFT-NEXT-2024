#include "stdafx.h"
#include "SDamage.h"

#include "../Components/Components.h"
#include "../Util/Utils.h"

void SDamage::Update(Scene& scene, float dt)
{
    RegenHealth(scene,dt);
    auto damageEvents = scene.reg.GetEntities<CDamageEvent>();
    for (auto damage_event : damageEvents)
    {
        CDamageEvent* event = scene.reg.GetComponent<CDamageEvent>(damage_event);
        CHealth* health = scene.reg.GetComponent<CHealth>(event->target);
        health->hp-= event->damage;
        
    }
    
    for (const auto health_id : scene.reg.GetEntities<CHealth>())
    {
        const CHealth* health = scene.reg.GetComponent<CHealth>(health_id);
        if(health->hp<=0)
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
            float healthPercentage = health->hp/health->maxHp;
            healthPercentage = 1-healthPercentage;
            render->OutlineColor ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
            /*if (healthPercentage>0.66f)
            {
                render->OutlineColor={1.0f,1.0f,1.0f};
                
            }
            else if (healthPercentage>0.33f)
            {
                render->OutlineColor= {0.8f,0.8f,0.0f};
                
            }
            else
            {
                render->OutlineColor={0.9f,0.1f,0.1f};
            }*/
        }
        
    }
    scene.reg.ClearEntities<CDamageEvent>();
}

void SDamage::RegenHealth(Scene& scene, float dt)
{
    for (auto element : scene.reg.GetEntities<CHealth>())
    {
        CHealth* health = scene.reg.GetComponent<CHealth>(element);
        health->hp = Utils::Clamp(health->hp+health->regenRate*dt,0.0f,health->maxHp);
    }
}
