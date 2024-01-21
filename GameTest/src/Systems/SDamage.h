#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
class SDamage : public ISystem
{
public:
    void update(Registry& Registry, float dt);
private:
    void resolveDamageEvents(Registry& Registry);
    void updateHealth(Registry& Registry, float dt);
    void deleteDead(Registry& Registry);
    
    
};
