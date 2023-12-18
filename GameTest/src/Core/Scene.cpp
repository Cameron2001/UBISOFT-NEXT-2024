#include "stdafx.h"
#include "Scene.h"
#include "ComponentArray.h"
#include "../Components/CTransform.h"

Scene::Scene()
{
    //create Component arrays
}

void Scene::Init()
{
    m_player = CreateEntity();
    
    auto transformArray = ComponentArray<CTransform>(32);
    transformArray.AddComponent(m_player, CTransform(vec2(5,5),90));
    bool test = transformArray.HasEntity(m_player);
    auto component = transformArray.GetComponent(m_player);
    
    
    
}

void Scene::Update(float dt)
{
    
}

void Scene::Render()
{
    
}

void Scene::Shutdown()
{
    
}

Entity Scene::CreateEntity()
{
    m_entityArray.push_back(1);
    return 1;
}

void Scene::DeleteEntity(Entity entityID)
{
}

template <typename T>
bool Scene::HasComponent(Entity entityID)
{
    
    return true;
}

template <typename T>
T Scene::GetComponent(Entity entityID)
{
    return 0;
}

template <typename T>
void Scene::AddComponent(Entity entityID, T component)
{
}

template <typename T>
void Scene::DeleteComponent(Entity entityID, T component)
{
}

template <typename T>
void Scene::CreateComponentArray()
{
}

template <typename T>
T Scene::GetComponentArray()
{
    return 0;
}

template <typename T>
void Scene::CreateSystem()
{
}

template <typename T>
T Scene::GetSystem()
{
    return 0;
}



