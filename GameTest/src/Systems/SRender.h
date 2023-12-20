#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"

class SRender: public ISystem
{
public:
    void Update(Scene* scene);
    
};
