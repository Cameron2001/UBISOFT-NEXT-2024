#include "stdafx.h"
#include "STimer.h"

#include "../Components/CLabel.h"
#include "../Components/CTimer.h"

void STimer::Update(Scene& scene, float dt)
{
    for (const auto element : scene.reg.GetEntities<CTimer>())
    {
        CTimer* timer = scene.reg.GetComponent<CTimer>(element);
        timer->timer+=dt;
    }
    UpdateTimerLabels(scene);
}

void STimer::UpdateTimerLabels(Scene& scene)
{
    for (const auto element : scene.reg.GetEntities<CTimer,CLabel>())
    {
        CLabel* label = scene.reg.GetComponent<CLabel>(element);
        CTimer* timer = scene.reg.GetComponent<CTimer>(element);
        const auto test = "Timer: " + std::to_string(timer->timer);
        
        label->labelText = test;
        
    }
}
