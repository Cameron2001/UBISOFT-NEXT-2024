//------------------------------------------------------------------------
// Registry.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ComponentArray.h"
#include "../Systems/ISystem.h"
//------------------------------------------------------------------------
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
private:
    std::vector<Entity> m_entityArray; //just a vector of uint32_t. Hold all entity ids
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentMap; //map of sparse sets of components
    std::unordered_map<const char*, std::shared_ptr<ISystem>> m_systemMap; //map of systems
    std::deque<Entity> m_freeList;
    
    
};


inline Registry::Registry()
{
    //Populating the list of free entity IDS
    for (Entity i = 1; i<MAX_IDS; i++)
    {
        m_freeList.push_back(i);
    }
}

inline Entity Registry::createEntity()
{
    Entity ID = m_freeList.front(); //Get free ID from m_freeList
    m_freeList.pop_front(); //remove grabbed ID from list of available
    m_entityArray.push_back(ID); //Add id to list of entity IDs
    return ID;
}

inline void Registry::deleteEntity(Entity entityID)
{
    //remove ID from list of entity IDs
    m_entityArray.erase(std::remove(m_entityArray.begin(), m_entityArray.end(), entityID), m_entityArray.end());
    //delete all components that belong to ID
    for (auto componentArray : m_componentMap)
    {
        if (componentArray.second->hasComponent(entityID))
            componentArray.second->removeComponent(entityID);
    }
    m_freeList.push_back(entityID); //Add freed ID to list of available
}

inline void Registry::clearAllEntities()
{
    for (const auto entity : m_entityArray) deleteEntity(entity); //Delete all entities
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

    //Key created based on type
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
    //Key created based on type
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
    std::vector<Entity> matches;

    //if empty return all ids
    if (sizeof...(Ts) == 0)
        return m_entityArray;
    
    for (auto entityID : m_entityArray)
    {
        bool match = true;
        //unpack parameter pack
        int arr[] = {hasComponent<Ts>(entityID)... };
        for (auto type : arr)
        {
            if(type!=true) match = false;
        }
        //if has all components it is a match
        if (match) matches.push_back(entityID);
    } 
    return matches;
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

