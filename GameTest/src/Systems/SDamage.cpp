#include "stdafx.h"
#include "SDamage.h"

#include "../Components/Components.h"
#include "../Util/Utils.h"

void SDamage::Update(Scene& scene, float dt)
{
    ResolveDamageEvents(scene);
    UpdateHealth(scene,dt);
    
}

void SDamage::ResolveDamageEvents(Scene& scene)
{
    const auto damageEvents = scene.reg.GetEntities<CDamageEvent>();
    for (const auto damage_event : damageEvents)
    {
        const CDamageEvent* event = scene.reg.GetComponent<CDamageEvent>(damage_event);
        CHealth* health = scene.reg.GetComponent<CHealth>(event->target);
        health->hp-= event->damage;
    }
    scene.reg.ClearEntities<CDamageEvent>();
}

void SDamage::UpdateHealth(Scene& scene, float dt)
{
    for (const auto element : scene.reg.GetEntities<CHealth>())
    {
        CHealth* health = scene.reg.GetComponent<CHealth>(element);
        if(health->hp<=0)
        {
            if(scene.reg.HasComponent<CPlayer>(element))
            {
                //end game
            }
            else
                scene.reg.DeleteEntity(element);
        }
        if(scene.reg.HasComponent<CRender>(element))
        {
            CRender* render = scene.reg.GetComponent<CRender>(element);
            float healthPercentage = health->hp/health->maxHp;
            healthPercentage = 1-healthPercentage;
            render->OutlineColor ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
        }
        health->hp = Utils::Clamp(health->hp+health->regenRate*dt,0.0f,health->maxHp);
    }
}


