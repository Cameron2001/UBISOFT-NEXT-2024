#include "stdafx.h"
#include "PlayScene.h"


#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void PlayScene::Init()
{
    Entity invalid = Registry.CreateEntity();
    CreateSystems();
    CreateComponentArrays();
    CreateMap();
    
    Factory::CreatePlayer(Registry,{100,100},24,10,150.0f, 100.0f, 1000.0f,50000.0f,30.0f,30.0f,20,35,1.0f);
    Factory::CreateWaveController(Registry,7.5f);
    Factory::CreateGameTimer(Registry,{50.0f,728.0f});
    
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    Registry.GetSystem<STimer>()->Update(Registry,dt);
    Registry.GetSystem<SPlayer>()->Update(Registry,dt);
    Registry.GetSystem<SEnemy>()->Update(Registry,dt);
    Registry.GetSystem<SButton>()->Update(Registry);
    Registry.GetSystem<SArm>()->Update(Registry);
    Registry.GetSystem<SPhysics>()->Update(Registry,dt);
    Registry.GetSystem<SDamage>()->Update(Registry,dt);
    
}

void PlayScene::Render()
{
    Registry.GetSystem<SRender>()->Update(Registry);
}

void PlayScene::Shutdown()
{
    Registry.ClearAllEntities();
}

void PlayScene::CreateSystems()
{
    Registry.CreateSystem<SPlayer>();
    Registry.CreateSystem<SPhysics>();
    Registry.CreateSystem<SRender>();
    Registry.CreateSystem<SEnemy>();
    Registry.CreateSystem<SDamage>();
    Registry.CreateSystem<SButton>();
    Registry.CreateSystem<STimer>();
    Registry.CreateSystem<SArm>();
    
}
void PlayScene::CreateComponentArrays()
{
    Registry.CreateComponentArray<CTransform>();
    Registry.CreateComponentArray<CRigidbody>();
    Registry.CreateComponentArray<CCollisionEvent>();
    Registry.CreateComponentArray<CDamageEvent>();
    Registry.CreateComponentArray<CBoxCollider>();
    Registry.CreateComponentArray<CCircleCollider>();
    Registry.CreateComponentArray<CRender>();
    Registry.CreateComponentArray<CPlayer>();
    Registry.CreateComponentArray<CHealth>();
    Registry.CreateComponentArray<CDamage>();
    Registry.CreateComponentArray<CButton>();
    Registry.CreateComponentArray<CEnemyTank>();
    Registry.CreateComponentArray<CEnemyHoming>();
    Registry.CreateComponentArray<CTimer>();
    Registry.CreateComponentArray<CScoreKeeper>();
    Registry.CreateComponentArray<CLabel>();
    Registry.CreateComponentArray<CShield>();
    Registry.CreateComponentArray<CWave>();
    Registry.CreateComponentArray<CArm>();
}

void PlayScene::CreateMap()
{
    float x= 129;
    for (int i = 0; i < 4; ++i)
    {
        Factory::CreateWall(Registry,{x*(float)i*2+x,31},{x,30},200);
    }
    for (int j = 0; j < 4; ++j)
    {
        Factory::CreateWall(Registry,{x*(float)j*2+x,737},{x,30},200);
    }
    
}
