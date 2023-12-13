#pragma once
//template stuff
//this is a sparseSet
template <class T>
class ComponentArray
{
public:
    ComponentArray()
    {
        capacity = 32;
        maxVal = 32;
        sparse = new uint32_t[maxVal+1];
        dense = new uint32_t[capacity];
        componentList = new T[capacity];
        n=0;
    }
    ComponentArray(uint32_t max, uint32_t cap)
    {
        sparse = new uint32_t[max+1];
        dense = new uint32_t[cap];
        componentList = new T[cap];
        capacity = cap;
        maxVal = max;
        n=0;
    }
    ~ComponentArray()
    {
        delete[] sparse;
        delete[] dense;
        
    }
    
    void AddComponent(Entity entityID, T component); //insert new element
    void RemoveComponent(Entity entityID); //remove element
    bool HasComponent(Entity entityID);
    void Clear();

private:
    
    uint32_t maxVal;
    uint32_t capacity;
    uint32_t n;
    uint32_t *sparse; //indices
    uint32_t *dense; //list 
    T *componentList;
    //dense is index of componemts in spare array. Index of components is also the entityID of the owning entity of said component
    //meaning that the dense array is a list of entityID's that contain said component
};


template <typename T>
void ComponentArray<T>::AddComponent(Entity entityID, T component)
{
    componentList[n] = component;
    dense[n] = entityID;
    sparse[entityID] = n;
    n++;
}

template <typename T>
void ComponentArray<T>::RemoveComponent(Entity entityID)
{
    
}

template <typename T>
bool ComponentArray<T>::HasComponent(Entity entityID)
{
    return true;
}

template <typename T>
void ComponentArray<T>::Clear()
{
    n=0;
}


