#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"
class SProjectile : public ISystem
{
public:
    void Update(Scene& scene, float dt);
    
};
