#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Util/Utils.h"

void SRender::Init(Scene& scene)
{
}

void SRender::Update(Scene& scene)
{
    for(auto entityID : scene.reg.GetEntities<CRender,CTransform>())
    {
        CRender* render = scene.reg.GetComponent<CRender>(entityID);
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        
        if(scene.reg.HasComponent<CBoxCollider>(entityID))
        {
            CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(entityID);
            DrawSquare(transform->pos,box->extents,render->Color);
        }
        if(scene.reg.HasComponent<CCircleCollider>(entityID))
        {
            CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(entityID);
            DrawCircle(transform->pos,circle->radius,16,render->Color);
        }
    }
    DrawPlayer(scene);
}

void SRender::DrawPlayer(Scene& scene)
{
    for (auto element : scene.reg.GetEntities<CPlayer>())
    {
        CTransform* playerTransform = scene.reg.GetComponent<CTransform>(element);
        CPlayer* playerComponent = scene.reg.GetComponent<CPlayer>(element);
        vec2 dir = {cosf(playerComponent->rot),sinf(playerComponent->rot)};
        vec3 color = {1.0f,1.0f,1.0f};
        dir*=playerComponent->aimLength;
        auto playerState = playerComponent->state;
        if (playerState == CPlayer::States::SHOOTING)
            color = {1.0f,0.0f,0.0f};
        if (playerState==CPlayer::States::RELOADING)
            color = {1.0f,1.0f,0.0f};
        App::DrawLine(playerTransform->pos.x,playerTransform->pos.y, playerTransform->pos.x+dir.x,playerTransform->pos.y+dir.y,color.x,color.y,color.z);
    }
    
}

void SRender::DrawSquare(vec2 pos, vec2 extents, vec3 color)
{
    vec2 bottomLeft = {pos.x-extents.x,pos.y-extents.y};
    vec2 bottomRight = {pos.x+extents.x, pos.y-extents.y};
    vec2 topLeft = {pos.x-extents.x,pos.y+extents.y};
    vec2 topRight = {pos.x+extents.x, pos.y+extents.y};
    
    App::DrawLine(bottomLeft.x,bottomLeft.y, topLeft.x,topLeft.y,color.x,color.y,color.z); //bottom left to top left
    App::DrawLine(topLeft.x,topLeft.y,topRight.x,topRight.y,color.x,color.y,color.z); //top left to top right
    App::DrawLine(topRight.x,topRight.y, bottomRight.x,bottomRight.y,color.x,color.y,color.z); //top right to bottom right
    App::DrawLine(bottomRight.x,bottomRight.y,bottomLeft.x,bottomLeft.y,color.x,color.y,color.z); //bottom right to bottom left
}

void SRender::DrawCircle(vec2 centre, float radius, int segments, vec3 color)
{
    for (int i = 0; i < segments; i++)
    {
        float angle = Utils::Deg2Rad*360/segments;
        App::DrawLine(cos(angle*i)*radius + centre.x, sin(angle*i)*radius+centre.y,cos(angle*(i+1))*radius + centre.x, sin(angle*(i+1))*radius+centre.y,color.x,color.y,color.z);
    }
}

