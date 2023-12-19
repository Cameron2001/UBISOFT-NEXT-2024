#include "stdafx.h"
#include "Scene.h"
#include "ComponentArray.h"
#include "../Components/CTransform.h"

Scene::Scene(): m_player(0)
{
    //create Component arrays
}

void Scene::Init()
{
    m_player = CreateEntity();
    CreateComponentArray<CTransform>();
    auto array = GetComponentArray<CTransform>();
    
    array->AddComponent(m_player,CTransform());
    auto has = array->HasComponent(m_player);
    
    has = HasComponent<CTransform>(m_player);
    
    array->RemoveComponent(m_player);

    has = array->HasComponent(m_player);

    has = HasComponent<CTransform>(m_player);
    
    
    
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
    entityNum++;
    m_entityArray.push_back(entityNum);
    return entityNum;
}

void Scene::DeleteEntity(Entity entityID)
{
}


template <typename T>
bool Scene::HasComponent(Entity entityID)
{
    auto array =GetComponentArray<T>();
    return array->HasComponent(entityID);
}

template <typename T>
T Scene::GetComponent(Entity entityID)
{
    auto array =GetComponentArray<T>();
    return array->GetComponent(entityID);
}

template <typename T>
void Scene::AddComponent(Entity entityID, T component)
{
    auto array =GetComponentArray<T>();
    array->AddComponent(entityID,component);
}

template <typename T>
void Scene::RemoveComponent(Entity entityID, T component)
{
    auto array =GetComponentArray<T>();
    array->RemoveComponent(entityID);
}

template <typename T>
void Scene::CreateComponentArray()
{
    /*m_componentTypes.push_back(typeid(T).name());
    m_componentArrays.push_back(new ComponentArray<T>());*/
    m_componentMap.insert({typeid(T).name(),new ComponentArray<T>()});
}

template <typename T>
ComponentArray<T>* Scene::GetComponentArray()
{
    /*auto it = std::find(m_componentTypes.begin(),m_componentTypes.end(), typeid(T).name());
    return static_cast<ComponentArray<T>*>(m_componentArrays[it-m_componentTypes.begin()]);*/
    //need to make this as fast as possible
    return static_cast<ComponentArray<T>*>(m_componentMap.at(typeid(T).name()));

    
}

template <typename T>
bool Scene::HasComponentArray()
{
    return false;
}







