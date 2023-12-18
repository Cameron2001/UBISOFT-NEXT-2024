#pragma once
#include "IComponentArray.h"
//template stuff
//this is a sparseSet
template <class T>
class ComponentArray : IComponentArray
{
public:
    ComponentArray(uint32_t cap = 32):
        capacity(cap),
        sparse(std::vector<uint32_t>(capacity, 0))
    {}
    
    void AddComponent(Entity entityID, T component); //insert new element
    void RemoveComponent(Entity entityID); //remove element
    bool HasEntity(Entity entityID);
    T GetComponent(Entity entityID);
    void Clear();

private:
    
    uint32_t capacity;
    std::vector<uint32_t> sparse; //indices
    std::vector<uint32_t> dense; //list
    std::vector<T> componentList;
    //T *componentList;
    //dense is index of componemts in spare array. Index of components is also the entityID of the owning entity of said component
    //meaning that the dense array is a list of entityID's that contain said component
};


template <typename T>
void ComponentArray<T>::AddComponent(Entity entityID, T component)
{
    const auto pos = dense.size();
    dense.push_back(entityID);
    componentList.push_back(component);
    sparse[entityID] = pos;
}

template <typename T>
void ComponentArray<T>::RemoveComponent(Entity entityID)
{
    const auto last = dense.back();
    std::swap(dense.back(), dense[sparse[entityID]]);
    std::swap(componentList.back(), componentList[sparse[entityID]]);
    std::swap(sparse[last], sparse[entityID]);
    dense.pop_back();
    componentList.pop_back();
}

template <class T>
T ComponentArray<T>::GetComponent(Entity entityID)
{
    if(!HasEntity(entityID))
        return {};
    return componentList[sparse[entityID]];
}


template <typename T>
void ComponentArray<T>::Clear()
{
    
}

template <class T>
bool ComponentArray<T>::HasEntity(Entity entityID)
{
    return (entityID < sparse.size() && sparse[entityID] < dense.size() && dense[sparse[entityID]] == entityID);
}


