#include "stdafx.h"
#include "DeathScene.h"

#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"

void DeathScene::init()
{
    //play death sound?
    Entity invalid = Registry.createEntity();
    createSystems();
    createComponentArrays();
    createMenu();
}

void DeathScene::update(float dt)
{
    Registry.getSystem<SButton>()->update(Registry);
}

void DeathScene::render()
{
    Registry.getSystem<SRender>()->update(Registry);
}

void DeathScene::shutdown()
{
    Registry.clearAllEntities();
}

void DeathScene::createSystems()
{
    Registry.createSystem<SRender>();
    Registry.createSystem<SButton>();
}

void DeathScene::createComponentArrays()
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

void DeathScene::createMenu()
{
    Factory::createLabel(Registry, "YOU DIED" , {500,600}, {0,0},{1.0f,0.0f,0.0f});
    Factory::createButton(Registry, {512,100},{100,30},CButton::ButtonTypes::EXIT,"Exit");
    Factory::createButton(Registry, {512,500},{100,30},CButton::ButtonTypes::START, "Restart");
}
