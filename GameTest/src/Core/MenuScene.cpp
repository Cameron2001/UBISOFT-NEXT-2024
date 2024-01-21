#include "stdafx.h"
#include "MenuScene.h"

#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"


void MenuScene::init()
{
    Entity invalid = Registry.createEntity();
    createSystems();
    createComponentArrays();
    createMenu();

    
    
    
    
    
    
    
}

void MenuScene::update(float dt)
{
    dt/=1000.0f;
    Registry.getSystem<SButton>()->update(Registry);
}

void MenuScene::render()
{
    Registry.getSystem<SRender>()->update(Registry);
}

void MenuScene::shutdown()
{
}

void MenuScene::createSystems()
{
    Registry.createSystem<SRender>();
    Registry.createSystem<SButton>();
}

void MenuScene::createComponentArrays()
{
    Registry.createComponentArray<CTransform>();
    Registry.createComponentArray<CRigidbody>();
    Registry.createComponentArray<CCollisionEvent>();
    Registry.createComponentArray<CDamageEvent>();
    Registry.createComponentArray<CBoxCollider>();
    Registry.createComponentArray<CCircleCollider>();
    Registry.createComponentArray<CRender>();
    Registry.createComponentArray<CPlayer>();
    Registry.createComponentArray<CHealth>();
    Registry.createComponentArray<CDamage>();
    Registry.createComponentArray<CButton>();
    Registry.createComponentArray<CEnemyTank>();
    Registry.createComponentArray<CEnemyHoming>();
    Registry.createComponentArray<CTimer>();
    Registry.createComponentArray<CLabel>();
    Registry.createComponentArray<CShield>();
    Registry.createComponentArray<CWave>();
    Registry.createComponentArray<CArm>();
}

void MenuScene::createMenu()
{
    Factory::createButton(Registry, {512,100},{100,30},CButton::ButtonTypes::EXIT,"Exit");
    Factory::createButton(Registry, {512,500},{100,30},CButton::ButtonTypes::START, "Start");
}

