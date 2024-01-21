//------------------------------------------------------------------------
// ComponentArray.h
// Templated sparse set implementation
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "IComponentArray.h"
//------------------------------------------------------------------------
template <class T>
class ComponentArray : public IComponentArray
{
public:
    ComponentArray():m_sparse(std::vector<uint32_t>(MAX_IDS, 0)){}
    
    void addComponent(Entity entityID, T component);
    void removeComponent(Entity entityID) override;
    bool hasComponent(Entity entityID) override; 
    T* getComponent(Entity entityID); 

private:
    
    std::vector<uint32_t> m_sparse; //indices
    std::vector<uint32_t> m_dense; //list
    std::vector<T> m_componentList;
    //dense is index of componemts in spare array. Index of components is also the entityID of the owning entity of said component
    //meaning that the dense array is a list of entityID's that contain said component
};


template <typename T>
void ComponentArray<T>::addComponent(Entity entityID, T component)
{
    //assert("Add component" && !HasComponent(entityID));
    const auto pos = m_dense.size();
    m_dense.push_back(entityID);
    m_componentList.push_back(component);
    m_sparse[entityID] = pos;
}

template <typename T>
void ComponentArray<T>::removeComponent(Entity entityID)
{
    //assert("remove component" && HasComponent(entityID));
    const auto last = m_dense.back();
    std::swap(m_dense.back(), m_dense[m_sparse[entityID]]);
    std::swap(m_componentList.back(), m_componentList[m_sparse[entityID]]);
    std::swap(m_sparse[last], m_sparse[entityID]);
    m_dense.pop_back();
    m_componentList.pop_back();
}

template <class T>
T* ComponentArray<T>::getComponent(Entity entityID)
{
    return &m_componentList[m_sparse[entityID]];
}


template <class T>
bool ComponentArray<T>::hasComponent(Entity entityID)
{
    return entityID < m_sparse.size() && m_sparse[entityID] < m_dense.size() && m_dense[m_sparse[entityID]] == entityID;
}


