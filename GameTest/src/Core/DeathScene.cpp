//------------------------------------------------------------------------
// DeathScene.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "DeathScene.h"
//------------------------------------------------------------------------
#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"
//------------------------------------------------------------------------
void DeathScene::init()
{
    //play death sound?
    createSystems();
    createComponentArrays();
    createMenu();
}

void DeathScene::update(float dt)
{
    registry.getSystem<SButton>()->update(registry);
}

void DeathScene::render()
{
    registry.getSystem<SRender>()->update(registry);
}

void DeathScene::shutdown()
{
    registry.clearAllEntities();
}

void DeathScene::createSystems()
{
    registry.createSystem<SRender>();
    registry.createSystem<SButton>();
}

void DeathScene::createComponentArrays()
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
    registry.createComponentArray<CWave>();
    registry.createComponentArray<CArm>();
}

void DeathScene::createMenu()
{
    factory::createLabel(registry, "YOU DIED", {465.0f,600.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f});
    factory::createLabel(registry, "You survived for: "+std::to_string(timeSurvived), {400.0f,500.0f});
    factory::createButton(registry, {512.0f,200.0f},{100.0f,50.0f},CButton::ButtonTypes::EXIT,"Exit");
    factory::createButton(registry, {512.0f,400.0f},{100.0f,50.0f},CButton::ButtonTypes::START, "Restart");
}
