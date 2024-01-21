#include "stdafx.h"
#include "SDamage.h"

#include "../../app/app.h"
#include "../Components/Components.h"
#include "../Core/DeathScene.h"
#include "../Core/SceneManager.h"
#include "../Util/Utils.h"

void SDamage::Update(Registry& Registry, float dt)
{
    ResolveDamageEvents(Registry);
    UpdateHealth(Registry,dt);
    DeleteDead(Registry);
    
    
}

void SDamage::ResolveDamageEvents(Registry& Registry)
{
    const auto damageEvents = Registry.GetEntities<CDamageEvent>();
    for (const auto damage_event : damageEvents)
    {
        const CDamageEvent* event = Registry.GetComponent<CDamageEvent>(damage_event);
        CHealth* health = Registry.GetComponent<CHealth>(event->target);
        health->hp-= event->damage;
        App::PlaySound(".\\Audio\\hitHurt.wav");
    }
    Registry.ClearEntities<CDamageEvent>();
}

void SDamage::UpdateHealth(Registry& Registry, float dt)
{
    for (const auto element : Registry.GetEntities<CHealth>())
    {
        CHealth* health = Registry.GetComponent<CHealth>(element);
        if(health->hp<=0)
        {
            health->isDead = true;
            App::PlaySound(".\\Audio\\death.wav");
        }
        if(Registry.HasComponent<CRender>(element))
        {
            CRender* render = Registry.GetComponent<CRender>(element);
            float healthPercentage = health->hp/health->maxHp;
            healthPercentage = 1-healthPercentage;
            render->color ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
        }
        health->hp = Utils::Clamp(health->hp+health->regenRate*dt,0.0f,health->maxHp);
    }
}

void SDamage::DeleteDead(Registry& Registry)
{
    bool player = false;
    for (const auto element: Registry.GetEntities<CHealth>())
    {
        CHealth* health = Registry.GetComponent<CHealth>(element);
        if(health->isDead)
        {
            if(Registry.HasComponent<CPlayer>(element)) player = true;
            Registry.DeleteEntity(element);
        }
        
    }
    if(player) SceneManager::GetInstance()->LoadScene<DeathScene>();
}


