#pragma once
#include "../Core/Registry.h"

class STimer : public ISystem
{
public:
    void Update(Registry& Registry, float dt);
private:
    void UpdateTimerLabels(Registry& Registry);
    
};
