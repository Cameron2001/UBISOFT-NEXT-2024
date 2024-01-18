#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"

class SAudio : public ISystem
{
public:
    void Update(Scene& scene);
    
};
