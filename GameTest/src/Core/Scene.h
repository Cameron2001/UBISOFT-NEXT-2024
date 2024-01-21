#pragma once
#include "Registry.h"
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init(){};
    virtual void Update(float dt){};
    virtual void Render(){};
    virtual void Shutdown(){};
    
    Registry reg;
    
    //maybe create some type of storage to contain all systems in
    //maybe vector isnt correct storage. If an entity is removed the index and entityID will no longer be alligned
    
};
