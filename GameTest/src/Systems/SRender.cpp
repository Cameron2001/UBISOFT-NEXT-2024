#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"

void SRender::Update(Scene* scene)
{
    auto test = scene->m_register.GetEntities<CRender>();
    
    for(auto entityID : scene->m_register.GetEntities<CRender>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRender* render = scene->m_register.GetComponent<CRender>(entityID);

        if(scene->m_register.HasComponent<CBoxCollider>(entityID))
        {
            CBoxCollider* box = scene->m_register.GetComponent<CBoxCollider>(entityID);
            DrawSquare(transform->pos.x-box->extents.x,transform->pos.y-box->extents.y,transform->pos.x+box->extents.x,transform->pos.y+box->extents.y);
        }
        
    }
}

void SRender::DrawSquare(float xMin, float yMin, float xMax, float yMax)
{
    App::DrawLine(xMin, yMin, xMin,yMax);
    App::DrawLine(xMin, yMin, xMax,yMin);
    App::DrawLine(xMax, yMax, xMin,yMax);
    App::DrawLine(xMax, yMax, xMax,yMin);
}
