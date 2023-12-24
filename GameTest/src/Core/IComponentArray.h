#pragma once


class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void RemoveComponent(Entity entityID)=0;
    virtual bool HasComponent(Entity entityID)=0;
};

