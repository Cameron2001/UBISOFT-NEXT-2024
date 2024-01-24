//------------------------------------------------------------------------
// SDamage.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ISystem.h"
#include "../Core/Registry.h"

//------------------------------------------------------------------------
class SDamage : public ISystem
{
public:
    static void update(Registry& registry, float dt);

private:
    static void resolveDamageEvents(Registry& registry);
    static void updateHealth(Registry& registry, float dt);
    static void deleteDead(Registry& registry);
};
