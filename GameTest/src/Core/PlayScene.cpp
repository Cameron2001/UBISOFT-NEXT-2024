#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/CImpulseEvent.h"
#include "../Components/Components.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SPlayer.h"
#include "../Systems/SRender.h"

PlayScene::~PlayScene()
=default;

void PlayScene::Init()
{
    m_register.CreateSystem<SPlayer>();
    m_register.CreateSystem<SPhysics>();
    m_register.CreateSystem<SRender>();
    
    m_register.CreateComponentArray<CPlayer>();
    m_register.CreateComponentArray<CTransform>();
    m_register.CreateComponentArray<CRigidbody>();
    m_register.CreateComponentArray<CRender>();
    m_register.CreateComponentArray<CBoxCollider>();
    m_register.CreateComponentArray<CCircleCollider>();
    m_register.CreateComponentArray<CCollider>();
    m_register.CreateComponentArray<CCollisionEvent>();
    m_register.CreateComponentArray<CImpulseEvent>();
    
    auto m_player = m_register.CreateEntity();
    m_register.AddComponent(m_player, CPlayer());
    m_register.AddComponent(m_player, CTransform({400,400}));
    m_register.AddComponent(m_player, CRigidbody());
    m_register.AddComponent(m_player, CRender());
    m_register.AddComponent(m_player,CCollider());
    //m_register.AddComponent(m_player,CCircleCollider{30});
    m_register.AddComponent(m_player,CBoxCollider({25,25}));

    auto m_box = m_register.CreateEntity();
    m_register.AddComponent(m_box, CTransform(vec2{500,500}));
    m_register.AddComponent(m_box, CRigidbody());
    m_register.AddComponent(m_box, CRender());
    m_register.AddComponent(m_box, CCollider());
    m_register.AddComponent(m_box,CBoxCollider({25,25}));

    auto m_circle= m_register.CreateEntity();
    m_register.AddComponent(m_circle, CTransform(vec2{300,300}));
    m_register.AddComponent(m_circle, CRigidbody());
    m_register.AddComponent(m_circle, CRender());
    m_register.AddComponent(m_circle, CCollider());
    m_register.AddComponent(m_circle,CCircleCollider{70});

    auto leftWall = m_register.CreateEntity();
    m_register.AddComponent(leftWall,CTransform{{1,500}});
    m_register.AddComponent(leftWall,CRender());
    m_register.AddComponent(leftWall, CCollider());
    m_register.AddComponent(leftWall,CBoxCollider{{0,600}});

    auto bottomWall = m_register.CreateEntity();
    m_register.AddComponent(bottomWall,CTransform{{700,1}});
    m_register.AddComponent(bottomWall,CRender());
    m_register.AddComponent(bottomWall, CCollider());
    m_register.AddComponent(bottomWall,CBoxCollider{{900,0}});

    auto rightWall = m_register.CreateEntity();
    m_register.AddComponent(rightWall,CTransform{{1600,500}});
    m_register.AddComponent(rightWall,CRender());
    m_register.AddComponent(rightWall, CCollider());
    m_register.AddComponent(rightWall,CBoxCollider{{0,600}});

    auto topWall = m_register.CreateEntity();
    m_register.AddComponent(topWall,CTransform{{700,900}});
    m_register.AddComponent(topWall,CRender());
    m_register.AddComponent(topWall, CCollider());
    m_register.AddComponent(topWall,CBoxCollider{{900,0}});
    //m_register.AddComponent(leftWall,CRigidbody());
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    m_register.GetSystem<SPlayer>()->Update(this,dt);
    
    m_register.GetSystem<SPhysics>()->Update(this,dt);
}

void PlayScene::Render()
{
    m_register.GetSystem<SRender>()->Update(this);
}

void PlayScene::Shutdown()
{
    
}
