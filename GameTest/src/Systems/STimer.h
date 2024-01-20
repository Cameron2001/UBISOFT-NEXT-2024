#pragma once
#include "../Core/Scene.h"

class STimer : public ISystem
{
public:
    void Update(Scene& scene, float dt);
    
};
