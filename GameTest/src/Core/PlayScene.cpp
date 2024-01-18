#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SDamage.h"
#include "../Systems/SDelete.h"
#include "../Systems/SLabel.h"
#include "../Systems/Systems.h"

void PlayScene::Init()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SFactory>();
    reg.CreateSystem<SDelete>();
    reg.CreateSystem<SLabel>();
    reg.CreateSystem<SDamage>();
    
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CImpulseEvent>();
    reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CEnemy>();
    reg.CreateComponentArray<CCamera>();
    reg.CreateComponentArray<CCollider>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CHealth>();
    reg.CreateComponentArray<CDeleteMe>();
    reg.CreateComponentArray<CLabel>();
    reg.CreateComponentArray<CDamageEvent>();
    reg.CreateComponentArray<CAngularImpulseEvent>();
    reg.CreateComponentArray<CColor>();
    reg.CreateComponentArray<CDamage>();
    
    
    reg.GetSystem<SFactory>()->CreateCamera(*this,{0,0});
    auto player = reg.GetSystem<SFactory>()->CreatePlayer(*this,{100,500},{25,30});
    reg.GetSystem<SFactory>()->CreateBox(*this,{350,350},{25,25},45);
    reg.GetSystem<SFactory>()->CreateCircle(*this,{100,100},60);
    reg.GetSystem<SFactory>()->CreateEnemy(*this,{500,100},{25,25},100);
    //reg.GetSystem<SFactory>()->CreateButton(*this, {500,600},{30,30});

    reg.AddComponent(player,CLabel("Player"));
    reg.AddComponent(player,CColor({0.5,1,0}));
    reg.GetSystem<SRender>()->Init(*this);
    reg.GetSystem<SPlayer>()->Init(*this);
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SPlayer>()->Update(*this,dt);
    reg.GetSystem<SPhysics>()->Update(*this,dt);
    reg.GetSystem<SDamage>()->Update(*this,dt);
    reg.GetSystem<SDelete>()->Update(*this);
}

void PlayScene::Render()
{
    reg.GetSystem<SRender>()->Update(*this);
    reg.GetSystem<SLabel>()->Update(*this);
}

void PlayScene::Shutdown()
{
    
}
