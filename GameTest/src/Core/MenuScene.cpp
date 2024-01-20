#include "stdafx.h"
#include "MenuScene.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void MenuScene::Init()
{
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SButton>();
    reg.CreateSystem<SFactory>();
    reg.CreateSystem<SLabel>();

    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CLabel>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CLabel>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CPlayer>();

    SFactory* factory = reg.GetSystem<SFactory>();
    Entity invalid = reg.CreateEntity();
    factory->CreateButton(*this, {500,100},{100,30},CButton::ButtonTypes::EXIT,"Exit");
    factory->CreateButton(*this, {500,300},{100,30},CButton::ButtonTypes::TUTORIAL, "Tutorial");
    factory->CreateButton(*this, {500,500},{100,30},CButton::ButtonTypes::START, "Start");
    

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
    reg.GetSystem<SLabel>()->Update(*this);
}

void MenuScene::Shutdown()
{
}
