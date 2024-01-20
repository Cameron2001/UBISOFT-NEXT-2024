#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SDamage.h"
#include "../Systems/SLabel.h"
#include "../Systems/STimer.h"
#include "../Systems/Systems.h"

void PlayScene::Init()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SFactory>();
    reg.CreateSystem<SDamage>();
    reg.CreateSystem<SButton>();
    reg.CreateSystem<STimer>();
    
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
    
    
    auto factory = reg.GetSystem<SFactory>();
    
    
    //reg.GetSystem<SFactory>()->CreateBox(*this, {300,300}, {500,20});
    //reg.GetSystem<SFactory>()->CreateEnemy(*this,{100,500},{54,55},50);
    Entity invalid = reg.CreateEntity();
    factory->CreatePlayer(*this,{100,100},25);
    factory->CreateWall(*this,{500,20},{550,20},1000);
    factory->CreateWall(*this,{500,748},{550,20},1000);;
    factory->CreateCircle(*this, {500,700},30);
    factory->CreateCircle(*this, {700,75},30);
    factory->CreateCircle(*this, {700,700},30);
    factory->CreateEnemyTank(*this, {500,500},{60,25},25,200,50);
    factory->CreateEnemyTank(*this, {600,200},{40,15},15,150,50);
    reg.GetSystem<SRender>()->Init(*this);
    reg.GetSystem<SPlayer>()->Init(*this);
   
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
