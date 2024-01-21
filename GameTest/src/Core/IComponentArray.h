#pragma once


class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void removeComponent(Entity entityID)=0;
    virtual bool hasComponent(Entity entityID)=0;
};

