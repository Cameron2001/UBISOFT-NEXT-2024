#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"

class SArm : public ISystem
{
public:
    void update(Registry& registry);
    
};
