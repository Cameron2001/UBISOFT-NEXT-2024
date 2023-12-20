#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/CPlayer.h"
#include "../Components/CTransform.h"
#include "../Systems/SPlayer.h"

PlayScene::~PlayScene()
=default;

void PlayScene::Init()
{
    m_register.CreateSystem<SPlayer>();
    m_register.CreateComponentArray<CPlayer>();
    m_player = m_register.CreateEntity();
    m_register.AddComponent(m_player, CPlayer());
}

void PlayScene::Update(float dt)
{
    m_register.GetSystem<SPlayer>()->Update(this);
}

void PlayScene::Render()
{
    
}

void PlayScene::Shutdown()
{
    
}
