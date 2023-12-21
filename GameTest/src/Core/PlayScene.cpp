#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/CPlayer.h"
#include "../Components/CTransform.h"
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
    
    m_player = m_register.CreateEntity();
    m_register.AddComponent(m_player, CPlayer());
    m_register.AddComponent(m_player, CTransform(vec2{500,400}));
    m_register.AddComponent(m_player, CRigidbody());
    m_register.AddComponent(m_player, CRender());
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
