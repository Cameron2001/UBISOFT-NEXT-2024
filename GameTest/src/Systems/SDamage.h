#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
class SDamage : public ISystem
{
public:
    void update(Registry& registry, float dt);
private:
    void resolveDamageEvents(Registry& registry);
    void updateHealth(Registry& registry, float dt);
    void deleteDead(Registry& registry);
    
    
};
