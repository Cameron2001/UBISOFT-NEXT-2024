#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/CTransform.h"
#include "../Systems/SPlayer.h"

PlayScene::~PlayScene()
=default;

void PlayScene::Init()
{
    m_register.CreateSystem<SPlayer>();
    m_register.CreateComponentArray<CTransform>();
}

void PlayScene::Update(float dt)
{
    
}

void PlayScene::Render()
{
    
}

void PlayScene::Shutdown()
{
    
}
