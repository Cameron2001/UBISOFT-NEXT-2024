#pragma once
#include "Camera.h"

class Scene
{
public:
    Scene();
    void Init();
    void Update(float dt);
    void Render();
    void Shutdown();
    
    Entity CreateEntity();
    void DeleteEntity(Entity entityID);

    template<typename T>
    bool HasComponent(Entity entityID);

    template<typename T>
    T GetComponent(Entity entityID);

    template<typename T>
    void AddComponent(Entity entityID, T component);

    template<typename T>
    void DeleteComponent(Entity entityID, T component);

    Camera GetCamera();
private:
    std::vector<Entity> m_entities;
    Camera m_camera;
    //create 2d array that holds component array
};
