#pragma once
#include <unordered_map>

template <class T>
class ComponentMap
{
public:
    ComponentMap();
    ~ComponentMap();
    void AddComponent(Entity entityID, T component);
    void RemoveComponent(Entity entityID);
    T GetComponent(Entity entityID);
    bool HasComponent(Entity entityID);
private:
    std::vector<T> componentStorage;
    std::unordered_map<Entity,T> componentMap;
};

template <typename T>
ComponentMap<T>::ComponentMap()
{
}

template <typename T>
ComponentMap<T>::~ComponentMap()
{
    componentMap.clear();
}

template <typename T>
void ComponentMap<T>::AddComponent(Entity entityID, T component)
{
    componentStorage.push_back(component);
    componentMap.insert({entityID, component});
}

template <typename T>
void ComponentMap<T>::RemoveComponent(Entity entityID)
{
    componentMap.erase(entityID);
}

template <typename T>
T ComponentMap<T>::GetComponent(Entity entityID)
{
    return componentMap.find(entityID)->second;
}

template <typename T>
bool ComponentMap<T>::HasComponent(Entity entityID)
{
    if(componentMap.find(entityID) != componentMap.end())
    {
        return true;
    }
    return false;
}
