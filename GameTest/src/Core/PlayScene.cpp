#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SEnemy.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SPlayer.h"
#include "../Systems/SRender.h"

PlayScene::~PlayScene()
=default;

void PlayScene::Init()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CCollider>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CImpulseEvent>();
    reg.CreateComponentArray<CCamera>();

    auto camera = reg.CreateEntity();
    reg.AddComponent(camera, CCamera());
    reg.AddComponent(camera, CTransform({0,0}));
    
    auto m_player = reg.CreateEntity();
    reg.AddComponent(m_player, CPlayer());
    reg.AddComponent(m_player, CTransform({400,400}));
    reg.AddComponent(m_player, CRigidbody());
    reg.AddComponent(m_player, CRender());
    reg.AddComponent(m_player,CCollider());
    //m_register.AddComponent(m_player,CCircleCollider{30});
    reg.AddComponent(m_player,CBoxCollider({25,25}));

    auto m_box = reg.CreateEntity();
    reg.AddComponent(m_box, CTransform({500,500}));
    reg.AddComponent(m_box, CRigidbody());
    reg.AddComponent(m_box, CRender());
    reg.AddComponent(m_box, CCollider());
    reg.AddComponent(m_box,CBoxCollider({25,25}));

    auto m_circle= reg.CreateEntity();
    reg.AddComponent(m_circle, CTransform({300,300}));
    reg.AddComponent(m_circle, CRigidbody());
    reg.AddComponent(m_circle, CRender());
    reg.AddComponent(m_circle, CCollider());
    reg.AddComponent(m_circle,CCircleCollider{70});

    auto leftWall = reg.CreateEntity();
    reg.AddComponent(leftWall,CTransform{{1,500}});
    reg.AddComponent(leftWall,CRender());
    reg.AddComponent(leftWall, CCollider());
    reg.AddComponent(leftWall,CBoxCollider{{0,600}});

    auto bottomWall = reg.CreateEntity();
    reg.AddComponent(bottomWall,CTransform{{700,1}});
    reg.AddComponent(bottomWall,CRender());
    reg.AddComponent(bottomWall, CCollider());
    reg.AddComponent(bottomWall,CBoxCollider{{900,0}});

    auto rightWall = reg.CreateEntity();
    reg.AddComponent(rightWall,CTransform{{1600,500}});
    reg.AddComponent(rightWall,CRender());
    reg.AddComponent(rightWall, CCollider());
    reg.AddComponent(rightWall,CBoxCollider{{0,600}});

    auto topWall = reg.CreateEntity();
    reg.AddComponent(topWall,CTransform{{700,900}});
    reg.AddComponent(topWall,CRender());
    reg.AddComponent(topWall, CCollider());
    reg.AddComponent(topWall,CBoxCollider{{900,0}});
    //m_register.AddComponent(leftWall,CRigidbody());

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
