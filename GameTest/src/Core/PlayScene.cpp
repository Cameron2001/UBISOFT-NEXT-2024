#include "stdafx.h"
#include "PlayScene.h"


#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"

void PlayScene::Init()
{
    Entity invalid = reg.CreateEntity();
    CreateSystems();
    CreateComponentArrays();
    CreateMap();
    
    Factory::CreatePlayer(reg,{100,100},20);
    Factory::CreatePlayerShield(reg, {100,100},20, 100);
    Factory::CreateWaveController(reg,10.0f);
    
    
    Factory::CreateGameTimer(reg,{300.0f,300.0f});
    
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<STimer>()->Update(reg,dt);
    reg.GetSystem<SPhysics>()->Update(reg,dt);
    reg.GetSystem<SPlayer>()->Update(reg,dt);
    reg.GetSystem<SEnemy>()->Update(reg,dt);
    reg.GetSystem<SDamage>()->Update(reg,dt);
    reg.GetSystem<SButton>()->Update(reg);
}

void PlayScene::Render()
{
    reg.GetSystem<SRender>()->Update(reg);
}

void PlayScene::Shutdown()
{
    reg.ClearAllEntities();
}

void PlayScene::CreateSystems()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SDamage>();
    reg.CreateSystem<SButton>();
    reg.CreateSystem<STimer>();
    
}
void PlayScene::CreateComponentArrays()
{
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CDamageEvent>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CHealth>();
    reg.CreateComponentArray<CDamage>();
    reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CEnemyTank>();
    reg.CreateComponentArray<CEnemyHoming>();
    reg.CreateComponentArray<CTimer>();
    reg.CreateComponentArray<CScoreKeeper>();
    reg.CreateComponentArray<CLabel>();
    reg.CreateComponentArray<CShield>();
    reg.CreateComponentArray<CWave>();
    reg.CreateComponentArray<CArm>();
}

void PlayScene::CreateMap()
{
    float bruh = 129;
    for (int i = 0; i < 4; ++i)
    {
        Factory::CreateWall(reg,{bruh*(float)i*2+bruh,31},{bruh,30},200);
    }
    for (int j = 0; j < 4; ++j)
    {
        Factory::CreateWall(reg,{bruh*(float)j*2+bruh,737},{bruh,30},200);
    }
    
}
