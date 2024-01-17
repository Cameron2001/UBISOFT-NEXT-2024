#include "stdafx.h"
#include "SDelete.h"

#include "../Components/Components.h"

void SDelete::Update(Scene& scene)
{
    
    for (auto ID : scene.reg.GetEntities<CDeleteMe>())
    {
        //optimize this
        scene.reg.m_entityArray.erase(std::remove(scene.reg.m_entityArray.begin(), scene.reg.m_entityArray.end(), ID), scene.reg.m_entityArray.end());
        for (auto element : scene.reg.m_componentMap)
        {
            if (element.second->HasComponent(ID))
                element.second->RemoveComponent(ID);
        }
        scene.reg.freeList.push_back(ID);
    }
}

void SDelete::ClearEvents(Scene& scene)
{
    scene.reg.ClearEntities<CImpulseEvent>();
    scene.reg.ClearEntities<CCollisionEvent>();
    scene.reg.ClearEntities<CDamageEvent>();
    scene.reg.ClearEntities<CButtonClickEvent>();
}
