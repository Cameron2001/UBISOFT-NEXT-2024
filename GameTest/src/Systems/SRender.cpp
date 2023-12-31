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
    App::DrawLine(pos.x-1,pos.y-1,pos.x+1,pos.y+1); //centre
    
}

void SRender::DrawCircle(vec2 centre, float radius)
{
    App::DrawLine(centre.x,centre.y-radius,centre.x-radius,centre.y);
    App::DrawLine(centre.x-radius,centre.y,centre.x,centre.y+radius);
    App::DrawLine(centre.x,centre.y+radius,centre.x+radius,centre.y);
    App::DrawLine(centre.x+radius,centre.y,centre.x,centre.y-radius);
    App::DrawLine(centre.x-1,centre.y-1,centre.x+1,centre.y+1);
}

void SRender::DrawPlane(vec2 pos)
{
    
}
