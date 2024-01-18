#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Util/Utils.h"

void SRender::Init(Scene& scene)
{
    //cameraTransform = scene.reg.GetComponent<CTransform>(scene.reg.GetEntities<CCamera>()[0]);
}

void SRender::Update(Scene& scene)
{
    for(auto entityID : scene.reg.GetEntities<CRender>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        vec3 color = {1,1,1};
        if(scene.reg.HasComponent<CColor>(entityID))
            color = scene.reg.GetComponent<CColor>(entityID)->rgbValue;

        if(scene.reg.HasComponent<CBoxCollider>(entityID))
        {
            CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(entityID);
            DrawSquare(transform->pos,box->extents,transform->rot,color);
        }
        if(scene.reg.HasComponent<CCircleCollider>(entityID))
        {
            CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(entityID);
            DrawCircle(transform->pos,circle->radius,16,color);
        }
        
    }
}

void SRender::DrawSquare(vec2 pos, vec2 extents, float rotation, vec3 color)
{
    //pos.x = pos.x * cosf(rotation) - pos.y * sinf(rotation);
    //pos.y = pos.x * sinf(rotation) + pos.y * cosf(rotation);
    //pos-=cameraTransform->pos;
    vec2 bottomLeft = Utils::Rotate({pos.x-extents.x,pos.y-extents.y},rotation,pos);
    vec2 bottomRight = Utils::Rotate({pos.x+extents.x, pos.y-extents.y},rotation,pos);
    vec2 topLeft = Utils::Rotate({pos.x-extents.x,pos.y+extents.y},rotation,pos);
    vec2 topRight = Utils::Rotate({pos.x+extents.x, pos.y+extents.y},rotation,pos);
    
    App::DrawLine(bottomLeft.x,bottomLeft.y, topLeft.x,topLeft.y,color.x,color.y,color.z); //bottom left to top left
    App::DrawLine(topLeft.x,topLeft.y,topRight.x,topRight.y,color.x,color.y,color.z); //top left to top right
    App::DrawLine(topRight.x,topRight.y, bottomRight.x,bottomRight.y,color.x,color.y,color.z); //top right to bottom right
    App::DrawLine(bottomRight.x,bottomRight.y,bottomLeft.x,bottomLeft.y,color.x,color.y,color.z); //bottom right to bottom left
    //App::DrawLine(pos.x-1,pos.y-1,pos.x+1,pos.y+1);
    
}

void SRender::DrawCircle(vec2 centre, float radius, int segments, vec3 color)
{
    //centre-=cameraTransform->pos;
    for (int i = 0; i < segments; i++)
    {
        float angle = Utils::Deg2Rad*360/segments;
        App::DrawLine(cos(angle*i)*radius + centre.x, sin(angle*i)*radius+centre.y,cos(angle*(i+1))*radius + centre.x, sin(angle*(i+1))*radius+centre.y);
    }
}

