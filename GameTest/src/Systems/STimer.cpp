#include "stdafx.h"
#include "STimer.h"

#include "../Components/CTimer.h"

void STimer::Update(Scene& scene, float dt)
{
    for (auto element : scene.reg.GetEntities<CTimer>())
    {
        CTimer* timer = scene.reg.GetComponent<CTimer>(element);
        timer->timer+=dt;
    }
}
