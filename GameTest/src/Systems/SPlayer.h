#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"
class SPlayer : public ISystem
{
public:
    void Init(Scene& scene);
    void Update(Scene& scene, float dt);
    Entity m_camera;
    bool shot = false;
};
