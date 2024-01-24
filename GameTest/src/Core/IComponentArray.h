//------------------------------------------------------------------------
// IComponentArray.h
// Interface for component arrays. Useful for storage 
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    //Can be called without knowing type
    //Useful for deleting all components from an entity
    virtual void removeComponent(Entity entityID) =0;
    virtual bool hasComponent(Entity entityID) =0;
};
