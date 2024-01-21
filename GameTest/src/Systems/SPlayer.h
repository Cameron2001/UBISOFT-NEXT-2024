//------------------------------------------------------------------------
// SPlayer.h
//------------------------------------------------------------------------
#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
class SPlayer : public ISystem
{
public:
    void update(Registry& registry, float dt);
};
