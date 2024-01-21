#include "stdafx.h"
#include "PlayScene.h"


#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void PlayScene::init()
{
    Entity invalid = Registry.createEntity();
    createSystems();
    createComponentArrays();
    createMap();
    
    Factory::createPlayer(Registry,{100,100},24,10,150.0f, 100.0f, 1000.0f,50000.0f,30.0f,30.0f,20,35,1.0f);
    Factory::createWaveController(Registry,7.5f);
    Factory::createGameTimer(Registry,{50.0f,728.0f});
    
   
}

void PlayScene::update(float dt)
{
    dt/=1000.0f;
    Registry.getSystem<STimer>()->update(Registry,dt);
    Registry.getSystem<SPlayer>()->update(Registry,dt);
    Registry.getSystem<SEnemy>()->update(Registry,dt);
    Registry.getSystem<SButton>()->update(Registry);
    Registry.getSystem<SArm>()->update(Registry);
    Registry.getSystem<SPhysics>()->update(Registry,dt);
    Registry.getSystem<SDamage>()->update(Registry,dt);
    
}

void PlayScene::render()
{
    Registry.getSystem<SRender>()->update(Registry);
}

void PlayScene::shutdown()
{
    Registry.clearAllEntities();
}

void PlayScene::createSystems()
{
    Registry.createSystem<SPlayer>();
    Registry.createSystem<SPhysics>();
    Registry.createSystem<SRender>();
    Registry.createSystem<SEnemy>();
    Registry.createSystem<SDamage>();
    Registry.createSystem<SButton>();
    Registry.createSystem<STimer>();
    Registry.createSystem<SArm>();
    
}
void PlayScene::createComponentArrays()
{
    Registry.createComponentArray<CTransform>();
    Registry.createComponentArray<CRigidbody>();
    Registry.createComponentArray<CCollisionEvent>();
    Registry.createComponentArray<CDamageEvent>();
    Registry.createComponentArray<CBoxCollider>();
    Registry.createComponentArray<CCircleCollider>();
    Registry.createComponentArray<CRender>();
    Registry.createComponentArray<CPlayer>();
    Registry.createComponentArray<CHealth>();
    Registry.createComponentArray<CDamage>();
    Registry.createComponentArray<CButton>();
    Registry.createComponentArray<CEnemyTank>();
    Registry.createComponentArray<CEnemyHoming>();
    Registry.createComponentArray<CTimer>();
    Registry.createComponentArray<CLabel>();
    Registry.createComponentArray<CShield>();
    Registry.createComponentArray<CWave>();
    Registry.createComponentArray<CArm>();
}

void PlayScene::createMap()
{
    float x= 129;
    for (int i = 0; i < 4; ++i)
    {
        Factory::createWall(Registry,{x*(float)i*2+x,31},{x,30},200);
    }
    for (int j = 0; j < 4; ++j)
    {
        Factory::createWall(Registry,{x*(float)j*2+x,737},{x,30},200);
    }
    
}
