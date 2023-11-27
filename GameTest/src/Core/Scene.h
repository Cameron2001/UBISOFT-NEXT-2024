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
private:
    std::vector<Entity> m_entities;
    Camera m_camera;
    //create 2d array that holds component array
};
