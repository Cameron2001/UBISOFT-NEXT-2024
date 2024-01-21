#include "stdafx.h"
#include "DeathScene.h"

#include "Factory.h"
#include "../Components/Components.h"
#include "../Systems/Systems.h"

void DeathScene::Init()
{
    //play death sound?
    Entity invalid = Registry.CreateEntity();
    CreateSystems();
    CreateComponentArrays();
    CreateMenu();
}

void DeathScene::Update(float dt)
{
    Registry.GetSystem<SButton>()->Update(Registry);
}

void DeathScene::Render()
{
    Registry.GetSystem<SRender>()->Update(Registry);
}

void DeathScene::Shutdown()
{
    Registry.ClearAllEntities();
}

void DeathScene::CreateSystems()
{
    Registry.CreateSystem<SRender>();
    Registry.CreateSystem<SButton>();
}

void DeathScene::CreateComponentArrays()
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

void DeathScene::CreateMenu()
{
    Factory::CreateLabel(Registry, "YOU DIED" , {500,600}, {0,0},{1.0f,0.0f,0.0f});
    Factory::CreateButton(Registry, {512,100},{100,30},CButton::ButtonTypes::EXIT,"Exit");
    Factory::CreateButton(Registry, {512,500},{100,30},CButton::ButtonTypes::START, "Restart");
}
