#include "stdafx.h"
#include "MenuScene.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void MenuScene::Init()
{
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SButton>();

    const auto button = reg.CreateEntity();
    reg.AddComponent(button, CButton());
    reg.AddComponent(button,CTransform({500,500}));
    reg.AddComponent(button,CBoxCollider({100,100}));
    reg.AddComponent(button,CRender());

    const auto camera = reg.CreateEntity();
    reg.AddComponent(camera,CTransform({0,0}));
    reg.AddComponent(camera,CCamera());

    reg.GetSystem<SRender>()->Init(*this);
}

void MenuScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SButton>()->Update(*this,dt);
}

void MenuScene::Render()
{
    reg.GetSystem<SRender>()->Update(*this);
}

void MenuScene::Shutdown()
{
}
