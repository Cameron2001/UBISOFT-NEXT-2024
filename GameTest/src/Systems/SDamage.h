#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"
class SDamage : public ISystem
{
public:
    void Update(Scene& scene,float dt);
    
};
