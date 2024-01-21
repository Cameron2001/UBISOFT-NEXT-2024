//------------------------------------------------------------------------
// SDamage.cpp
//------------------------------------------------------------------------
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
        health.health-= event.damage;
        App::PlaySound(".\\Audio\\hitHurt.wav");
    }
    registry.clearEntities<CDamageEvent>();
}

void SDamage::updateHealth(Registry& registry, float dt)
{
    for (const Entity ID : registry.getEntities<CHealth>())
    {
        CHealth& health = registry.getComponent<CHealth>(ID);
        if(health.health<=0)
        {
            health.bDead = true;
            App::PlaySound(".\\Audio\\death.wav");
        }
        if(registry.hasComponent<CRender>(ID))
        {
            //clean this up
            CRender& render = registry.getComponent<CRender>(ID);
            float healthPercentage = health.health/health.maxHealth;
            healthPercentage = 1-healthPercentage;
            render.color ={1.0f,1.0f-healthPercentage,1.0f-healthPercentage};
        }
        health.health = utils::clamp(health.health+health.regenRate*dt,0.0f,health.maxHealth);
    }
}

void SDamage::deleteDead(Registry& registry)
{
    bool playerDead = false;
    for (const Entity ID: registry.getEntities<CHealth>())
    {
        const CHealth& health = registry.getComponent<CHealth>(ID);
        if(health.bDead)
        {
            if(registry.hasComponent<CPlayer>(ID)) playerDead = true;
            registry.deleteEntity(ID);
        }
    }
    if(playerDead) SceneManager::getInstance()->loadScene<DeathScene>();
}


