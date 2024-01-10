﻿#include "stdafx.h"
#include "MenuScene.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"

MenuScene::~MenuScene()
= default;

void MenuScene::Init()
{
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SButton>();

    /*reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CCamera>();
    reg.CreateComponentArray<CCircleCollider>();*/
    
    auto button = reg.CreateEntity();
    reg.AddComponent(button, CButton());
    reg.AddComponent(button,CTransform({500,500}));
    reg.AddComponent(button,CBoxCollider({100,100}));
    reg.AddComponent(button,CRender());

    auto camera = reg.CreateEntity();
    reg.AddComponent(camera,CTransform({0,0}));
    reg.AddComponent(camera,CCamera());

    reg.GetSystem<SRender>()->Init(this);
}

void MenuScene::Update(float dt)
{
    reg.GetSystem<SButton>()->Update(this,dt);
}

void MenuScene::Render()
{
    reg.GetSystem<SRender>()->Update(this);
}

void MenuScene::Shutdown()
{
}
