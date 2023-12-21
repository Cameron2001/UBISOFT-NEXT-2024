#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"

void SRender::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CRender>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRender* render = scene->m_register.GetComponent<CRender>(entityID);

        DrawSquare(transform->pos.x,transform->pos.y,transform->pos.x+10,transform->pos.y+10);
    }
}

void SRender::DrawSquare(float xMin, float yMin, float xMax, float yMax)
{
    App::DrawLine(xMin, yMin, xMin,yMax);
    App::DrawLine(xMin, yMin, xMax,yMin);
    App::DrawLine(xMax, yMax, xMin,yMax);
    App::DrawLine(xMax, yMax, xMax,yMin);
}
