#include "stdafx.h"
#include "SProjectile.h"

#include "SFactory.h"
#include "../Components/Components.h"

void SProjectile::Update(Scene& scene, float dt)
{
    for (auto element : scene.reg.GetEntities<CCollisionEvent>())
    {
        CCollisionEvent* event = scene.reg.GetComponent<CCollisionEvent>(element);
        if(scene.reg.HasComponent<CProjectile>(event->entityA))
        {
            scene.reg.AddComponent(event->entityA,CDeleteMe());
            scene.reg.GetSystem<SFactory>()->CreateDamageEvent(scene,event->entityB,50);
        }
        if(scene.reg.HasComponent<CProjectile>(event->entityB))
        {
            scene.reg.AddComponent(event->entityB,CDeleteMe());
            scene.reg.GetSystem<SFactory>()->CreateDamageEvent(scene,event->entityA,50);
        }
    }
}
