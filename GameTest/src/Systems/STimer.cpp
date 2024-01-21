#include "stdafx.h"
#include "STimer.h"

#include "../Components/CLabel.h"
#include "../Components/CTimer.h"

void STimer::Update(Registry& Registry, float dt)
{
    for (const auto element : Registry.GetEntities<CTimer>())
    {
        CTimer* timer = Registry.GetComponent<CTimer>(element);
        timer->timer+=dt;
    }
    UpdateTimerLabels(Registry);
}

void STimer::UpdateTimerLabels(Registry& Registry)
{
    for (const auto element : Registry.GetEntities<CTimer,CLabel>())
    {
        CLabel* label = Registry.GetComponent<CLabel>(element);
        CTimer* timer = Registry.GetComponent<CTimer>(element);
        const auto test = "Timer: " + std::to_string(timer->timer);
        
        label->labelText = test;
        
    }
}
