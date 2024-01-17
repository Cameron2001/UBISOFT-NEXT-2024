﻿#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SDamage.h"
#include "../Systems/SDelete.h"
#include "../Systems/SLabel.h"
#include "../Systems/SProjectile.h"
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
    reg.CreateSystem<SDelete>();
    reg.CreateSystem<SProjectile>();
    reg.CreateSystem<SLabel>();
    reg.CreateSystem<SDamage>();
    
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
    reg.CreateComponentArray<CDeleteMe>();
    reg.CreateComponentArray<CProjectile>();
    reg.CreateComponentArray<CLabel>();
    reg.CreateComponentArray<CDamageEvent>();
    
    
    reg.GetSystem<SFactory>()->CreateCamera(*this,{0,0});
    auto player = reg.GetSystem<SFactory>()->CreatePlayer(*this,{100,500},{25,30});
    reg.GetSystem<SFactory>()->CreateBox(*this,{500,400},{25,25});
    reg.GetSystem<SFactory>()->CreateCircle(*this,{100,100},60);
    reg.GetSystem<SFactory>()->CreateButton(*this, {500,600},{30,30});

    reg.AddComponent(player,CLabel("Player"));
    reg.GetSystem<SRender>()->Init(*this);
    reg.GetSystem<SPlayer>()->Init(*this);
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SPlayer>()->Update(*this,dt);
    reg.GetSystem<SPhysics>()->Update(*this,dt);
    reg.GetSystem<SProjectile>()->Update(*this,dt);
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
