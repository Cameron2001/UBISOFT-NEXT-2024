#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/Systems.h"

PlayScene::~PlayScene()
=default;

void PlayScene::Init()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SFactory>();
    
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CImpulseEvent>();
    reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CCamera>();
    reg.CreateComponentArray<CCollider>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CHealth>();
    
    reg.GetSystem<SFactory>()->CreateCamera(this,{0,0});
    reg.GetSystem<SFactory>()->CreatePlayer(this,{200,300},{50,25});
    reg.GetSystem<SFactory>()->CreateBox(this,{500,400},{25,25});
    reg.GetSystem<SFactory>()->CreateCircle(this,{100,100},60);
    reg.GetSystem<SFactory>()->CreateButton(this, {500,600},{30,30});
    
    reg.GetSystem<SRender>()->Init(this);
    reg.GetSystem<SPlayer>()->Init(this);
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SPlayer>()->Update(this,dt);
    reg.GetSystem<SPhysics>()->Update(this,dt);
}

void PlayScene::Render()
{
    reg.GetSystem<SRender>()->Update(this);
}

void PlayScene::Shutdown()
{
    
}
