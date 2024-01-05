#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Util/Utils.h"

void SRender::Update(Scene* scene)
{
    
    for(auto entityID : scene->m_register.GetEntities<CRender>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);

        if(scene->m_register.HasComponent<CBoxCollider>(entityID))
        {
            CBoxCollider* box = scene->m_register.GetComponent<CBoxCollider>(entityID);
            DrawSquare(transform->pos,box->extents);
        }
        if(scene->m_register.HasComponent<CCircleCollider>(entityID))
        {
            CCircleCollider* circle = scene->m_register.GetComponent<CCircleCollider>(entityID);
            DrawCircle(transform->pos,circle->radius);
        }
        
    }
}

void SRender::DrawSquare(vec2 pos, vec2 extents)
{
    App::DrawLine(pos.x-extents.x, pos.y-extents.y, pos.x-extents.x,pos.y+extents.y); //bottom left to top left
    App::DrawLine(pos.x-extents.x,pos.y+extents.y, pos.x+extents.x,pos.y+extents.y); //top left to top right
    App::DrawLine(pos.x+extents.x, pos.y+extents.y, pos.x+extents.x,pos.y-extents.y); //top right to bottom right
    App::DrawLine(pos.x+extents.x,pos.y-extents.y, pos.x-extents.x,pos.y-extents.y); //bottom right to bottom left
    //App::DrawLine(pos.x-1,pos.y-1,pos.x+1,pos.y+1);
    
}

void SRender::DrawCircle(vec2 centre, float radius, int segments)
{
    for (int i = 0; i < segments; i++)
    {
        float angle = Utils::Deg2Rad*360/segments;
        App::DrawLine(cos(angle*i)*radius + centre.x, sin(angle*i)*radius+centre.y,cos(angle*(i+1))*radius + centre.x, sin(angle*(i+1))*radius+centre.y);
    }
}

