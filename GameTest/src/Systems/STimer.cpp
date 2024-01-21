#include "stdafx.h"
#include "STimer.h"

#include "../Components/CLabel.h"
#include "../Components/CTimer.h"

void STimer::update(Registry& registry, float dt)
{
    for (const auto element : registry.getEntities<CTimer>())
    {
        CTimer& timer = registry.getComponent<CTimer>(element);
        timer.timer+=dt;
    }
    updateTimerLabels(registry);
}

void STimer::updateTimerLabels(Registry& registry)
{
    for (const auto element : registry.getEntities<CTimer,CLabel>())
    {
        CLabel& label = registry.getComponent<CLabel>(element);
        const CTimer& timer = registry.getComponent<CTimer>(element);
        label.labelText = "Timer: " + std::to_string(timer.timer);;
    }
}
