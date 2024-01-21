#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SDamage.h"
#include "../Systems/SLabel.h"
#include "../Systems/STimer.h"
#include "../Systems/Systems.h"

void PlayScene::Init()
{
    
    CreateSystems();
    CreateComponentArrays();
    
    auto factory = reg.GetSystem<SFactory>();
    Entity invalid = reg.CreateEntity();
    factory->CreatePlayer(*this,{100,100},25);
    CreateMap();


    
    factory->CreateEnemyTank(*this, {500,500},{60,25},25,200,50);
    factory->CreateEnemyTank(*this, {600,200},{40,15},15,150,50);
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<STimer>()->Update(*this,dt);
    reg.GetSystem<SPhysics>()->Update(*this,dt);
    reg.GetSystem<SPlayer>()->Update(*this,dt);
    reg.GetSystem<SDamage>()->Update(*this,dt);
    reg.GetSystem<SButton>()->Update(*this,dt);
    reg.GetSystem<SEnemy>()->Update(*this,dt);
}

void PlayScene::Render()
{
    reg.GetSystem<SRender>()->Update(*this);
}

void PlayScene::Shutdown()
{
    
}

void PlayScene::CreateSystems()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SFactory>();
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
}

void PlayScene::CreateMap()
{
    auto factory = reg.GetSystem<SFactory>();
    for (int i = 0; i < 11; ++i)
    {
        factory->CreateWall(*this,{51*(float)i*2,20},{50,20},200);
    }
    for (int j = 0; j < 11; ++j)
    {
        factory->CreateWall(*this,{51*(float)j*2,748},{50,20},200);
    }
    
}
