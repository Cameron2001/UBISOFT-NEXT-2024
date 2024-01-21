#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Registry.h"
class SPlayer : public ISystem
{
public:
    void update(Registry& Registry, float dt);
};
