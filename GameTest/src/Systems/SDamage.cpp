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
    for (const Entity ID : registry.getEntities<CDamageEvent>())
    {
        const CDamageEvent& event = registry.getComponent<CDamageEvent>(ID);
        CHealth& health = registry.getComponent<CHealth>(event.target);
        health.hp-= event.damage;
        App::PlaySound(".\\Audio\\hitHurt.wav");
    }
    registry.clearEntities<CDamageEvent>();
}

void SDamage::updateHealth(Registry& registry, float dt)
{
    for (const Entity ID : registry.getEntities<CHealth>())
    {
        CHealth& health = registry.getComponent<CHealth>(ID);
        if(health.hp<=0)
        {
            health.bDead = true;
            App::PlaySound(".\\Audio\\death.wav");
        }
        if(registry.hasComponent<CRender>(ID))
        {
            CRender& render = registry.getComponent<CRender>(ID);
            float healthPercentage = health.hp/health.maxHp;
            healthPercentage = 1-healthPercentage;
            render.color ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
        }
        health.hp = Utils::clamp(health.hp+health.regenRate*dt,0.0f,health.maxHp);
    }
}

void SDamage::deleteDead(Registry& registry)
{
    bool playerDead = false;
    for (const Entity ID: registry.getEntities<CHealth>())
    {
        CHealth& health = registry.getComponent<CHealth>(ID);
        if(health.bDead)
        {
            if(registry.hasComponent<CPlayer>(ID)) playerDead = true;
            registry.deleteEntity(ID);
        }
    }
    if(playerDead) SceneManager::getInstance()->loadScene<DeathScene>();
}


