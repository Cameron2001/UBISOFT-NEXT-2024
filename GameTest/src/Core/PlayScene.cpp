//------------------------------------------------------------------------
// PlayScene.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "PlayScene.h"
//------------------------------------------------------------------------
#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"
//------------------------------------------------------------------------


void PlayScene::init()
{
    createSystems();
    createComponentArrays();
    createMap();
    
    factory::createPlayer(registry,{100.0f,100.0f},24.0f,10,150.0f, 1000.0f,50000.0f,30.0f,30.0f,20.0f,35.0f,0.8f);
    factory::createWaveController(registry,7.5f);
    factory::createGameTimer(registry,{50.0f,728.0f});

    registry.getSystem<SEnemy>()->start(registry); //spawn first wave
    
   
}

void PlayScene::update(float dt)
{
    dt/=1000.0f;
    registry.getSystem<STimer>()->update(registry,dt);
    registry.getSystem<SPlayer>()->update(registry,dt);
    registry.getSystem<SEnemy>()->update(registry,dt);
    registry.getSystem<SButton>()->update(registry);
    registry.getSystem<SArm>()->update(registry);
    registry.getSystem<SPhysics>()->update(registry,dt);
    registry.getSystem<SDamage>()->update(registry,dt);
    
}

void PlayScene::render()
{
    registry.getSystem<SRender>()->update(registry);
}

void PlayScene::shutdown()
{
    registry.clearAllEntities();
}

void PlayScene::createSystems()
{
    registry.createSystem<SPlayer>();
    registry.createSystem<SPhysics>();
    registry.createSystem<SRender>();
    registry.createSystem<SEnemy>();
    registry.createSystem<SDamage>();
    registry.createSystem<SButton>();
    registry.createSystem<STimer>();
    registry.createSystem<SArm>();
    
}
void PlayScene::createComponentArrays()
{
    registry.createComponentArray<CTransform>();
    registry.createComponentArray<CRigidbody>();
    registry.createComponentArray<CCollisionEvent>();
    registry.createComponentArray<CDamageEvent>();
    registry.createComponentArray<CBoxCollider>();
    registry.createComponentArray<CCircleCollider>();
    registry.createComponentArray<CRender>();
    registry.createComponentArray<CPlayer>();
    registry.createComponentArray<CHealth>();
    registry.createComponentArray<CDamage>();
    registry.createComponentArray<CButton>();
    registry.createComponentArray<CEnemyTank>();
    registry.createComponentArray<CEnemyHoming>();
    registry.createComponentArray<CTimer>();
    registry.createComponentArray<CLabel>();
    registry.createComponentArray<CWave>();
    registry.createComponentArray<CArm>();
}

void PlayScene::createMap()
{
    float x= 129.0f;
    for (int i = 0; i < 4; ++i)
    {
        factory::createWall(registry,{x*(float)i*2+x,31.0f},{x,30.0f},175.0f);
    }
    for (int j = 0; j < 4; ++j)
    {
        factory::createWall(registry,{x*(float)j*2+x,737.0f},{x,30.0f},175.0f);
    }
    
}
