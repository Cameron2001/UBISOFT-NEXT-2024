#pragma once
#include "Camera.h"
#include "Registry.h"
class Scene
{
public:
    virtual ~Scene();
    virtual void Init();
    virtual void Update(float dt);
    virtual void Render();
    virtual void Shutdown();
    
    
    
    Camera m_camera;
    Registry m_register;
private:
    
    //maybe create some type of storage to contain all systems in
    //maybe vector isnt correct storage. If an entity is removed the index and entityID will no longer be alligned
    
    

    
};
