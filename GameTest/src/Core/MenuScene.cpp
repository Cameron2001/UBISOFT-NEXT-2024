#include "stdafx.h"
#include "MenuScene.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void MenuScene::Init()
{
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SButton>();
    reg.CreateSystem<SFactory>();

    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CDamageEvent>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CHealth>();
    reg.CreateComponentArray<CDamage>();
    reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CEnemyTank>();
    reg.CreateComponentArray<CEnemyHoming>();
    reg.CreateComponentArray<CTimer>();
    reg.CreateComponentArray<CScoreKeeper>();
    reg.CreateComponentArray<CLabel>();
    reg.CreateComponentArray<CShield>();
    reg.CreateComponentArray<CWave>();
    reg.CreateComponentArray<CArm>();
    
    Entity invalid = reg.CreateEntity();
    auto factory = reg.GetSystem<SFactory>();
    
    factory->CreateButton(*this, {500,100},{100,30},CButton::ButtonTypes::EXIT,"Exit");
    factory->CreateButton(*this, {500,300},{100,30},CButton::ButtonTypes::TUTORIAL, "Tutorial");
    factory->CreateButton(*this, {500,500},{100,30},CButton::ButtonTypes::START, "Start");
    
    
}

void MenuScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SButton>()->Update(*this);
}

void MenuScene::Render()
{
    reg.GetSystem<SRender>()->Update(*this);
}

void MenuScene::Shutdown()
{
}
