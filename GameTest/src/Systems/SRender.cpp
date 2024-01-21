#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Util/Utils.h"

void SRender::Update(Scene& scene)
{
    DrawShapes(scene);
    DrawPlayer(scene);
    DrawTank(scene);
    DrawLabels(scene);
}

void SRender::DrawPlayer(Scene& scene)
{
    for (auto element : scene.reg.GetEntities<CPlayer>())
    {
        const CTransform* playerTransform = scene.reg.GetComponent<CTransform>(element);
        const CPlayer* playerComponent = scene.reg.GetComponent<CPlayer>(element);
        const CCircleCollider* playerCircle = scene.reg.GetComponent<CCircleCollider>(element);
        CArm* arm = scene.reg.GetComponent<CArm>(element);
        vec2 armStart = {cosf(arm->rotation),sinf(arm->rotation)};
        const vec2 armEnd = armStart*arm->length;
        armStart*=playerCircle->radius;
        vec3 color = {1.0f,1.0f,1.0f};
        const auto playerState = playerComponent->state;
        if (playerState == CPlayer::States::SHOOTING)
            color = {1.0f,0.0f,0.0f};
        if (playerState==CPlayer::States::RELOADING)
            color = {1.0f,1.0f,0.0f};
        App::DrawLine(playerTransform->pos.x+armStart.x,playerTransform->pos.y+armStart.y, playerTransform->pos.x+armEnd.x,playerTransform->pos.y+armEnd.y,color.x,color.y,color.z);
    }
    
}

void SRender::DrawTank(Scene& scene)
{
    for(auto element : scene.reg.GetEntities<CEnemyTank>())
    {
        const CEnemyTank* tank = scene.reg.GetComponent<CEnemyTank>(element);
        const CTransform* transform = scene.reg.GetComponent<CTransform>(element);
        const CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(element);
        CArm* arm = scene.reg.GetComponent<CArm>(element);
        vec2 armStart  = {cosf(arm->rotation),sinf(arm->rotation)};
        vec2 armEnd = armStart*arm->length;
        //armStart*circle->radius;
        vec3 color = {1.0f,1.0f,1.0f};
        const auto tankState = tank->state;
        if (tankState==CEnemyTank::TankState::SHOOTING)
            color = {1.0f,0.0f,0.0f};
        if (tankState==CEnemyTank::TankState::RELOADING)
            color = {1.0f,1.0f,0.0f};
        App::DrawLine(transform->pos.x+armStart.x+circle->offset.x,transform->pos.y+armStart.y, transform->pos.x+armEnd.x+circle->offset.x,transform->pos.y+armEnd.y,color.x,color.y,color.z);
    }
}

void SRender::DrawShapes(Scene& scene)
{
    for(auto entityID : scene.reg.GetEntities<CRender>())
    {
        const CRender* render = scene.reg.GetComponent<CRender>(entityID);
        const CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        
        if(scene.reg.HasComponent<CBoxCollider>(entityID))
        {
            const CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(entityID);
            DrawSquare(transform->pos+box->offset,box->extents,render->OutlineColor);
        }
        if(scene.reg.HasComponent<CCircleCollider>(entityID))
        {
            const CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(entityID);
            DrawCircle(transform->pos+circle->offset,circle->radius,10, render->OutlineColor);
        }
    }
}

void SRender::DrawSquare(vec2 pos, vec2 extents, vec3 OutLinecolor)
{
    const vec2 bottomLeft = {pos.x-extents.x,pos.y-extents.y};
    const vec2 bottomRight = {pos.x+extents.x, pos.y-extents.y};
    const vec2 topLeft = {pos.x-extents.x,pos.y+extents.y};
    const vec2 topRight = {pos.x+extents.x, pos.y+extents.y};
    
    App::DrawLine(bottomLeft.x,bottomLeft.y, topLeft.x,topLeft.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //bottom left to top left
    App::DrawLine(topLeft.x,topLeft.y,topRight.x,topRight.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //top left to top right
    App::DrawLine(topRight.x,topRight.y, bottomRight.x,bottomRight.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //top right to bottom right
    App::DrawLine(bottomRight.x,bottomRight.y,bottomLeft.x,bottomLeft.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //bottom right to bottom left
    
}

void SRender::DrawCircle(vec2 centre, float radius, int segments, vec3 Outsidecolor)
{
    for (int i = 0; i < segments; i++)
    {
        const float angle = Utils::Deg2Rad*360/segments;
        App::DrawLine(cosf(angle*i)*radius + centre.x, sinf(angle*i)*radius+centre.y,cosf(angle*(i+1))*radius + centre.x, sinf(angle*(i+1))*radius+centre.y,Outsidecolor.x,Outsidecolor.y,Outsidecolor.z);
    }
}

void SRender::DrawLabels(Scene& scene)
{
    for (const auto current : scene.reg.GetEntities<CLabel>())
    {
        const CLabel* label = scene.reg.GetComponent<CLabel>(current);
        const CTransform* transform = scene.reg.GetComponent<CTransform>(current);
        App::Print(transform->pos.x+label->labelOffset.x,transform->pos.y+label->labelOffset.y,label->labelText.c_str(),25,25,25);
    }
}

void SRender::DrawArms(Scene& scene)
{
    for (auto element : scene.reg.GetEntities<CArm>())
    {
        CArm* arm = scene.reg.GetComponent<CArm>(element);
    }
}



