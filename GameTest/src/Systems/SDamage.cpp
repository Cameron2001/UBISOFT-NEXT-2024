#include "stdafx.h"
#include "SDamage.h"

#include "../../app/app.h"
#include "../Components/Components.h"
#include "../Core/DeathScene.h"
#include "../Core/SceneManager.h"
#include "../Util/Utils.h"

void SDamage::update(Registry& registry, float dt)
{
    resolveDamageEvents(registry);
    updateHealth(registry,dt);
    deleteDead(registry);
    
    
}

void SDamage::resolveDamageEvents(Registry& registry)
{
    const auto damageEvents = registry.getEntities<CDamageEvent>();
    for (const auto damage_event : damageEvents)
    {
        const CDamageEvent& event = registry.getComponent<CDamageEvent>(damage_event);
        CHealth& health = registry.getComponent<CHealth>(event.target);
        health.hp-= event.damage;
        App::PlaySound(".\\Audio\\hitHurt.wav");
    }
    registry.clearEntities<CDamageEvent>();
}

void SDamage::updateHealth(Registry& registry, float dt)
{
    for (const auto element : registry.getEntities<CHealth>())
    {
        CHealth& health = registry.getComponent<CHealth>(element);
        if(health.hp<=0)
        {
            health.bDead = true;
            App::PlaySound(".\\Audio\\death.wav");
        }
        if(registry.hasComponent<CRender>(element))
        {
            CRender& render = registry.getComponent<CRender>(element);
            float healthPercentage = health.hp/health.maxHp;
            healthPercentage = 1-healthPercentage;
            render.color ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
        }
        health.hp = Utils::Clamp(health.hp+health.regenRate*dt,0.0f,health.maxHp);
    }
}

void SDamage::deleteDead(Registry& registry)
{
    bool player = false;
    for (const auto element: registry.getEntities<CHealth>())
    {
        CHealth& health = registry.getComponent<CHealth>(element);
        if(health.bDead)
        {
            if(registry.hasComponent<CPlayer>(element)) player = true;
            registry.deleteEntity(element);
        }
        
    }
    if(player) SceneManager::getInstance()->loadScene<DeathScene>();
}


