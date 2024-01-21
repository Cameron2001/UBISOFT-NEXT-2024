//------------------------------------------------------------------------
// MenuScene.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "MenuScene.h"
//------------------------------------------------------------------------
#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"
//------------------------------------------------------------------------

void MenuScene::init()
{
    createSystems();
    createComponentArrays();
    createMenu();

    
    
    
    
    
    
    
}

void MenuScene::update(float dt)
{
    dt/=1000.0f;
    registry.getSystem<SButton>()->update(registry);
}

void MenuScene::render()
{
    registry.getSystem<SRender>()->update(registry);
}

void MenuScene::shutdown()
{
}

void MenuScene::createSystems()
{
    registry.createSystem<SRender>();
    registry.createSystem<SButton>();
}

void MenuScene::createComponentArrays()
{
    registry.createComponentArray<CTransform>();
    registry.createComponentArray<CRigidbody>();
    registry.createComponentArray<CCollisionEvent>();
    registry.createComponentArray<CDamageEvent>();
    registry.createComponentArray<CBoxCollider>();
    registry.createComponentArray<CCircleCollider>();
    registry.createComponentArray<CRender>();
    registry.createComponentArray<CPlayer>();
    registry.createComponentArray<CHealth>();
    registry.createComponentArray<CDamage>();
    registry.createComponentArray<CButton>();
    registry.createComponentArray<CEnemyTank>();
    registry.createComponentArray<CEnemyHoming>();
    registry.createComponentArray<CTimer>();
    registry.createComponentArray<CLabel>();
    registry.createComponentArray<CShield>();
    registry.createComponentArray<CWave>();
    registry.createComponentArray<CArm>();
}

void MenuScene::createMenu()
{
    factory::createLabel(registry, "Ubisoft NEXT 2024", {445.0f,600.0f});
    factory::createButton(registry, {512.0f,200.0f},{100.0f,50.0f},CButton::ButtonTypes::EXIT,"Exit");
    factory::createButton(registry, {512.0f,400.0f},{100.0f,50.0f},CButton::ButtonTypes::START, "Start");
}

