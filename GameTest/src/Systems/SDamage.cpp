#include "stdafx.h"
#include "SDamage.h"

#include "../../app/app.h"
#include "../Components/Components.h"
#include "../Core/DeathScene.h"
#include "../Core/SceneManager.h"
#include "../Util/Utils.h"

void SDamage::update(Registry& Registry, float dt)
{
    resolveDamageEvents(Registry);
    updateHealth(Registry,dt);
    deleteDead(Registry);
    
    
}

void SDamage::resolveDamageEvents(Registry& Registry)
{
    const auto damageEvents = Registry.getEntities<CDamageEvent>();
    for (const auto damage_event : damageEvents)
    {
        const CDamageEvent& event = Registry.getComponent<CDamageEvent>(damage_event);
        CHealth& health = Registry.getComponent<CHealth>(event.target);
        health.hp-= event.damage;
        App::PlaySound(".\\Audio\\hitHurt.wav");
    }
    Registry.clearEntities<CDamageEvent>();
}

void SDamage::updateHealth(Registry& Registry, float dt)
{
    for (const auto element : Registry.getEntities<CHealth>())
    {
        CHealth& health = Registry.getComponent<CHealth>(element);
        if(health.hp<=0)
        {
            health.isDead = true;
            App::PlaySound(".\\Audio\\death.wav");
        }
        if(Registry.hasComponent<CRender>(element))
        {
            CRender& render = Registry.getComponent<CRender>(element);
            float healthPercentage = health.hp/health.maxHp;
            healthPercentage = 1-healthPercentage;
            render.color ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
        }
        health.hp = Utils::Clamp(health.hp+health.regenRate*dt,0.0f,health.maxHp);
    }
}

void SDamage::deleteDead(Registry& Registry)
{
    bool player = false;
    for (const auto element: Registry.getEntities<CHealth>())
    {
        CHealth& health = Registry.getComponent<CHealth>(element);
        if(health.isDead)
        {
            if(Registry.hasComponent<CPlayer>(element)) player = true;
            Registry.deleteEntity(element);
        }
        
    }
    if(player) SceneManager::getInstance()->loadScene<DeathScene>();
}


