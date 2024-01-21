#pragma once
#include "../Core/Registry.h"

class STimer : public ISystem
{
public:
    void update(Registry& Registry, float dt);
private:
    void updateTimerLabels(Registry& Registry);
    
};
