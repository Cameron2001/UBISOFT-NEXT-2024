//------------------------------------------------------------------------
// Registry.h
//------------------------------------------------------------------------
#pragma once
#include "ComponentArray.h"
#include "../Systems/ISystem.h"

class Registry
{
public:
    Registry();
    Entity createEntity();
    void deleteEntity(Entity entityID);
    void deleteEntities();

    template<typename T>
    bool hasComponent(Entity entityID);

    template<typename T>
    T& getComponent(Entity entityID);

    template<typename T>
    void addComponent(Entity entityID, T component);

    template<typename T>
    void removeComponent(Entity entityID);

    template<typename T>
    void createComponentArray();

    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray();

    template<typename T>
    bool hasComponentArray() const;

    template<typename T>
    void createSystem();

    template<typename T>
    std::shared_ptr<T> getSystem();

    template<typename T>
    bool hasSystem() const;

    template<typename... Ts>
    std::vector<Entity> getEntities();
    

    template<typename T>
    void clearComponents();

    template<typename T>
    void clearEntities();

    void clearAllEntities();
    
    std::vector<Entity> m_entityArray; //just a vector of uint32_t. Hold all entity ids
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentMap;
    std::unordered_map<const char*, std::shared_ptr<ISystem>> m_systemMap;
    std::deque<Entity> freeList;
    
    
};


inline Registry::Registry()
{
    for (Entity i = 0; i<MAX_IDS; i++)
    {
        freeList.push_back(i);
    }
}

inline Entity Registry::createEntity()
{
    Entity id = freeList.front();
    freeList.pop_front();
    m_entityArray.push_back(id);
    return id;
}

inline void Registry::deleteEntity(Entity entityID)
{
    m_entityArray.erase(std::remove(m_entityArray.begin(), m_entityArray.end(), entityID), m_entityArray.end());
    for (auto element : m_componentMap)
    {
        if (element.second->hasComponent(entityID))
            element.second->removeComponent(entityID);
    }
    freeList.push_back(entityID);
}

inline void Registry::clearAllEntities()
{
    for (const auto entity : m_entityArray)
    {
        deleteEntity(entity);
    }
}

template <typename T>
bool Registry::hasComponent(Entity entityID)
{
    //assert("Has Component, Array not found" && HasComponentArray<T>());
    return getComponentArray<T>()->hasComponent(entityID);
}

template <typename T>
T& Registry::getComponent(Entity entityID)
{
    //assert("Get Component, Array not found" && HasComponentArray<T>());
    return *getComponentArray<T>()->getComponent(entityID);
}

template <typename T>
void Registry::addComponent(Entity entityID, T component)
{
    //assert("Add Component, Array not found" && HasComponentArray<T>());
    getComponentArray<T>()->addComponent(entityID,component);
}

template <typename T>
void Registry::removeComponent(Entity entityID)
{
    //assert("Remove Component, Array not found" && HasComponentArray<T>());
    getComponentArray<T>()->removeComponent(entityID);
}

template <typename T>
void Registry::createComponentArray()
{
    //assert("Create array, Array found" && !HasComponentArray<T>());
    m_componentMap.insert({typeid(T).name(),std::make_shared<ComponentArray<T>>()});
}

template <typename T>
std::shared_ptr<ComponentArray<T>> Registry::getComponentArray()
{
    //assert("Get Component Array, Array not found" && HasComponentArray<T>());
    
    return std::static_pointer_cast<ComponentArray<T>>(m_componentMap.at(typeid(T).name()));
}

template <typename T>
bool Registry::hasComponentArray() const
{
    return m_componentMap.count(typeid(T).name());
}

template <typename T>
void Registry::createSystem()
{
    m_systemMap.insert({typeid(T).name(),std::make_shared<T>()});
}

template <typename T>
std::shared_ptr<T> Registry::getSystem()
{
    return std::static_pointer_cast<T>(m_systemMap.at(typeid(T).name()));
}

template <typename T>
bool Registry::hasSystem() const
{
    return m_systemMap.count(typeid(T).name());
}

template <typename... Ts>
std::vector<Entity> Registry::getEntities()
{
    std::vector<Entity> entities;
    
    if (sizeof...(Ts) == 0)
        return m_entityArray;
    
    for (auto entityID : m_entityArray)
    {
        bool match = true;
        int arr[] = {hasComponent<Ts>(entityID)... };
        for (auto auto_ : arr)
        {
            if(auto_!=true) match = false;
        }
        if (match) entities.push_back(entityID);
    } 
    
    return entities;
}


template <typename T>
void Registry::clearComponents()
{
    for (auto entity : getEntities<T>())
    {
        removeComponent<T>(entity);
    }
    
}

template <typename T>
void Registry::clearEntities()
{
    for (auto entity : getEntities<T>())
    {
        deleteEntity(entity);
    }
}

