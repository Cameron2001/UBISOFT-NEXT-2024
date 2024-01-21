﻿#include "stdafx.h"
#include "MenuScene.h"

#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void MenuScene::Init()
{
    Entity invalid = Registry.CreateEntity();
    CreateSystems();
    CreateComponentArrays();
    CreateMenu();

    
    
    
    
    
    
    
}

void MenuScene::Update(float dt)
{
    dt/=1000.0f;
    Registry.GetSystem<SButton>()->Update(Registry);
}

void MenuScene::Render()
{
    Registry.GetSystem<SRender>()->Update(Registry);
}

void MenuScene::Shutdown()
{
}

void MenuScene::CreateSystems()
{
    Registry.CreateSystem<SRender>();
    Registry.CreateSystem<SButton>();
}

void MenuScene::CreateComponentArrays()
{
    Registry.CreateComponentArray<CTransform>();
    Registry.CreateComponentArray<CRigidbody>();
    Registry.CreateComponentArray<CCollisionEvent>();
    Registry.CreateComponentArray<CDamageEvent>();
    Registry.CreateComponentArray<CBoxCollider>();
    Registry.CreateComponentArray<CCircleCollider>();
    Registry.CreateComponentArray<CRender>();
    Registry.CreateComponentArray<CPlayer>();
    Registry.CreateComponentArray<CHealth>();
    Registry.CreateComponentArray<CDamage>();
    Registry.CreateComponentArray<CButton>();
    Registry.CreateComponentArray<CEnemyTank>();
    Registry.CreateComponentArray<CEnemyHoming>();
    Registry.CreateComponentArray<CTimer>();
    Registry.CreateComponentArray<CScoreKeeper>();
    Registry.CreateComponentArray<CLabel>();
    Registry.CreateComponentArray<CShield>();
    Registry.CreateComponentArray<CWave>();
    Registry.CreateComponentArray<CArm>();
}

void MenuScene::CreateMenu()
{
    Factory::CreateButton(Registry, {512,100},{100,30},CButton::ButtonTypes::EXIT,"Exit");
    Factory::CreateButton(Registry, {512,500},{100,30},CButton::ButtonTypes::START, "Start");
}

