#include "stdafx.h"
#include "ComponentArray.h"

ComponentArray::ComponentArray(uint32_t max, uint32_t cap)
{
    sparse = new uint32_t[max+1];
    dense = new uint32_t[cap];
    capacity = cap;
    maxVal = max;
    n=0;
}

ComponentArray::~ComponentArray()
{
    delete[] sparse;
    delete[] dense;
}

uint32_t ComponentArray::Search()
{
    
}

void ComponentArray::Insert()
{
}

void ComponentArray::Remove()
{
}

void ComponentArray::print()
{
}

void ComponentArray::Clear()
{
}
