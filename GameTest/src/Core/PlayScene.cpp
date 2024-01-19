#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SDamage.h"
#include "../Systems/SLabel.h"
#include "../Systems/Systems.h"

void PlayScene::Init()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SFactory>();
    reg.CreateSystem<SDamage>();
    
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CDamageEvent>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CEnemy>();
    reg.CreateComponentArray<CHealth>();
    reg.CreateComponentArray<CDamage>();
    
    
   
    
    
    //reg.GetSystem<SFactory>()->CreateBox(*this, {300,300}, {500,20});
    //reg.GetSystem<SFactory>()->CreateEnemy(*this,{100,500},{54,55},50);
    auto player = reg.GetSystem<SFactory>()->CreatePlayer(*this,{300,500},50);
    auto box = reg.GetSystem<SFactory>()->CreateBox(*this, {600,300}, {20,500});
    auto circle = reg.GetSystem<SFactory>()->CreateCircle(*this, {300,300}, 30);
    reg.AddComponent(circle,CRigidbody());
    //reg.GetSystem<SFactory>()->CreateButton(*this, {500,600},{30,30});
    reg.GetSystem<SRender>()->Init(*this);
    reg.GetSystem<SPlayer>()->Init(*this);
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SPhysics>()->Update(*this,dt);
    reg.GetSystem<SPlayer>()->Update(*this,dt);
    reg.GetSystem<SDamage>()->Update(*this,dt);
}

void PlayScene::Render()
{
    reg.GetSystem<SRender>()->Update(*this);
}

void PlayScene::Shutdown()
{
    
}
