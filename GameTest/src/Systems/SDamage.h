#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
class SDamage : public ISystem
{
public:
    void Update(Registry& Registry, float dt);
private:
    void ResolveDamageEvents(Registry& Registry);
    void UpdateHealth(Registry& Registry, float dt);
    void DeleteDead(Registry& Registry);
    
    
};
