#pragma once
#include "IComponentArray.h"
//template stuff
//this is a sparseSet
template <class T>
class ComponentArray : public IComponentArray
{
public:
    ComponentArray():sparse(std::vector<uint32_t>(MAX_IDS, 0)){}
    
    void AddComponent(Entity entityID, T component); //insert new element
    void RemoveComponent(Entity entityID) override; //remove element
    bool HasComponent(Entity entityID) override;
    T* GetComponent(Entity entityID);

private:
    
    std::vector<uint32_t> sparse; //indices
    std::vector<uint32_t> dense; //list
    std::vector<T> componentList;
    //dense is index of componemts in spare array. Index of components is also the entityID of the owning entity of said component
    //meaning that the dense array is a list of entityID's that contain said component
};


template <typename T>
void ComponentArray<T>::AddComponent(Entity entityID, T component)
{
    if(!HasComponent(entityID))
    {
        const auto pos = dense.size();
        dense.push_back(entityID);
        componentList.push_back(component);
        sparse[entityID] = pos;
    }
}

template <typename T>
void ComponentArray<T>::RemoveComponent(Entity entityID)
{
    if(HasComponent(entityID))
    {
        const auto last = dense.back();
        std::swap(dense.back(), dense[sparse[entityID]]);
        std::swap(componentList.back(), componentList[sparse[entityID]]);
        std::swap(sparse[last], sparse[entityID]);
        dense.pop_back();
        componentList.pop_back();
    }
}

template <class T>
T* ComponentArray<T>::GetComponent(Entity entityID)
{
    if(!HasComponent(entityID))
        return nullptr;
    return &componentList[sparse[entityID]];
}


template <class T>
bool ComponentArray<T>::HasComponent(Entity entityID)
{
    return entityID < sparse.size() && sparse[entityID] < dense.size() && dense[sparse[entityID]] == entityID;
}


