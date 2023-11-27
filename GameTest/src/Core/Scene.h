﻿#pragma once
#include "Camera.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SPlayer.h"
#include "../Systems/SRender.h"

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
    
    SPlayer m_systemPlayer;
    SRender m_systemRender;
    SPhysics m_systemPhysics;
    
    Camera m_camera;

    void UpdateSystems();
    //create 2d array that holds component array
};