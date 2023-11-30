#pragma once
//template stuff
//this is a sparseSet
template <typename T>
class ComponentArray
{
public:
    ComponentArray(uint32_t max, uint32_t cap)
    {
        sparse = new uint32_t[max+1];
        dense = new uint32_t[cap];
        capacity = cap;
        maxVal = max;
        n=0;
    }
    ~ComponentArray()
    {
        delete[] sparse;
        delete[] dense;
        
    }
    
    uint32_t Search(T value); //returns the index of value
    void Insert(T value); //insert new element
    void Remove(T value); //remove element
    void Print(); //prints the whole set
    void Clear(); //empty the set

private:
    uint32_t maxVal;
    uint32_t capacity;
    uint32_t n;
    T *sparse; 
    uint32_t *dense;
    //dense is index of componemts in spare array. Index of components is also the entityID of the owning entity of said component
    //meaning that the dense array is a list of entityID's that contain said component
};

template <typename T>
uint32_t ComponentArray<T>::Search(T value)
{
}

template <typename T>
void ComponentArray<T>::Insert(T value)
{
}

template <typename T>
void ComponentArray<T>::Remove(T value)
{
}

template <typename T>
void ComponentArray<T>::Print()
{
}

template <typename T>
void ComponentArray<T>::Clear()
{
    n=0;
}


