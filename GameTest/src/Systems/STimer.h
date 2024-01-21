#pragma once
#include "../Core/Registry.h"

class STimer : public ISystem
{
public:
    void update(Registry& registry, float dt);
private:
    void updateTimerLabels(Registry& registry);
    
};
