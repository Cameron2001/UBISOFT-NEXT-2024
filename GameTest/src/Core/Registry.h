#pragma once
#include <deque>
#include <unordered_map>

#include "ComponentArray.h"
#include "IComponentArray.h"
#include "../Systems/ISystem.h"

class Registry
{
public:
    Registry();
    Entity CreateEntity();
    void DeleteEntity(Entity entityID);
    void DeleteEntities();

    template<typename T>
    bool HasComponent(Entity entityID);

    template<typename T>
    T* GetComponent(Entity entityID);

    template<typename T>
    void AddComponent(Entity entityID, T component);

    template<typename T>
    void RemoveComponent(Entity entityID);

    template<typename T>
    void CreateComponentArray();

    template<typename T>
    ComponentArray<T>* GetComponentArray();

    template<typename T>
    bool HasComponentArray() const;

    template<typename T>
    void CreateSystem();

    template<typename T>
    T* GetSystem();

    template<typename T>
    bool HasSystem() const;

    template<typename T>
    std::vector<Entity> GetEntities();

    template<typename T>
    void ClearComponents();

    template<typename T>
    void ClearEntities();

    void ClearAllEntities();
    
    std::vector<Entity> m_entityArray; //just a vector of uint32_t. Hold all entity ids
    std::unordered_map<const char*, IComponentArray*> m_componentMap;
    std::unordered_map<const char*, ISystem*> m_systemMap;
    std::deque<Entity> freeList;
    
    
};


inline Registry::Registry()
{
    for (Entity i = 0; i<MAX_IDS; i++)
    {
        freeList.push_back(i);
    }
}

inline Entity Registry::CreateEntity()
{
    Entity id = freeList.front();
    freeList.pop_front();
    m_entityArray.push_back(id);
    return id;
}

inline void Registry::DeleteEntity(Entity entityID)
{
    //auto pos = std::find(m_entityArray.begin(),m_entityArray.end(), entityID);
    m_entityArray.erase(std::remove(m_entityArray.begin(), m_entityArray.end(), entityID), m_entityArray.end());
    for (auto element : m_componentMap)
    {
        if (element.second->HasComponent(entityID))
            element.second->RemoveComponent(entityID);
    }
    freeList.push_back(entityID);
    //AddComponent(entityID,CDeleteMe());
}

inline void Registry::ClearAllEntities()
{
    for (const auto entity : m_entityArray)
    {
        DeleteEntity(entity);
    }
}

template <typename T>
bool Registry::HasComponent(Entity entityID)
{
    //assert("Has Component, Array not found" && HasComponentArray<T>());
    return GetComponentArray<T>()->HasComponent(entityID);
}

template <typename T>
T* Registry::GetComponent(Entity entityID)
{
    //assert("Get Component, Array not found" && HasComponentArray<T>());
    return GetComponentArray<T>()->GetComponent(entityID);
}

template <typename T>
void Registry::AddComponent(Entity entityID, T component)
{
    //assert("Add Component, Array not found" && HasComponentArray<T>());
    GetComponentArray<T>()->AddComponent(entityID,component);
}

template <typename T>
void Registry::RemoveComponent(Entity entityID)
{
    //assert("Remove Component, Array not found" && HasComponentArray<T>());
    GetComponentArray<T>()->RemoveComponent(entityID);
}

template <typename T>
void Registry::CreateComponentArray()
{
    //assert("Create array, Array found" && !HasComponentArray<T>());
    m_componentMap.insert({typeid(T).name(),new ComponentArray<T>()});
}

template <typename T>
ComponentArray<T>* Registry::GetComponentArray()
{
    //assert("Get Component Array, Array not found" && HasComponentArray<T>());
    
    return static_cast<ComponentArray<T>*>(m_componentMap.at(typeid(T).name()));
}

template <typename T>
bool Registry::HasComponentArray() const
{
    return m_componentMap.count(typeid(T).name());
}

template <typename T>
void Registry::CreateSystem()
{
    m_systemMap.insert({typeid(T).name(),new T});
}

template <typename T>
T* Registry::GetSystem()
{
    return static_cast<T*>(m_systemMap.at(typeid(T).name()));
}

template <typename T>
bool Registry::HasSystem() const
{
    return m_systemMap.count(typeid(T).name());
}

template <typename T>
std::vector<Entity> Registry::GetEntities()
{
    //very important to optimize this
    std::vector<Entity> entities;
    for (auto entityID : m_entityArray)
    {
       if(HasComponent<T>(entityID))
       {
           entities.push_back(entityID);
       } 
    }
    return entities;
}

template <typename T>
void Registry::ClearComponents()
{
    for (auto entity : GetEntities<T>())
    {
        RemoveComponent<T>(entity);
    }
    
}

template <typename T>
void Registry::ClearEntities()
{
    for (auto entity : GetEntities<T>())
    {
        DeleteEntity(entity);
    }
}

