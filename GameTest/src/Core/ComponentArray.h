#pragma once
//template stuff
//this is a sparseSet
class ComponentArray
{
public:
    ComponentArray(uint32_t max, uint32_t cap);
    ~ComponentArray();
    
    uint32_t Search();
    void Insert();
    void Remove();
    void print();
    void Clear();

private:
    uint32_t maxVal;
    uint32_t capacity;
    uint32_t n;
    uint32_t *sparse;
    uint32_t *dense;
};


