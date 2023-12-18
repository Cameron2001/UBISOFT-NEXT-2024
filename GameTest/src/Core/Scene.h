﻿#pragma once
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

    template<typename T>
    void GetComponentArray();

    void SetCamera(Camera cam);
    Camera GetCamera();
private:
    std::vector<Entity> m_entityArray; //just a vector of uint32_t. Hold all entity ids 
    //maybe create some type of storage to contain all systems in
    //maybe vector isnt correct storage. If an entity is removed the index and entityID will no longer be alligned
    Camera m_camera;
    

    
    //create 2d array that holds component array
};
