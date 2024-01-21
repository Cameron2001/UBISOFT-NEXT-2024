#pragma once
#include "Registry.h"
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void init(){};
    virtual void update(float dt){};
    virtual void render(){};
    virtual void shutdown(){};
    
    Registry Registry;
    
    //maybe create some type of storage to contain all systems in
    //maybe vector isnt correct storage. If an entity is removed the index and entityID will no longer be alligned
    
};
