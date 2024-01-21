#include "stdafx.h"
#include "STimer.h"

#include "../Components/CLabel.h"
#include "../Components/CTimer.h"

void STimer::update(Registry& Registry, float dt)
{
    for (const auto element : Registry.getEntities<CTimer>())
    {
        CTimer& timer = Registry.getComponent<CTimer>(element);
        timer.timer+=dt;
    }
    updateTimerLabels(Registry);
}

void STimer::updateTimerLabels(Registry& Registry)
{
    for (const auto element : Registry.getEntities<CTimer,CLabel>())
    {
        CLabel& label = Registry.getComponent<CLabel>(element);
        CTimer& timer = Registry.getComponent<CTimer>(element);
        const auto test = "Timer: " + std::to_string(timer.timer);
        
        label.labelText = test;
        
    }
}
