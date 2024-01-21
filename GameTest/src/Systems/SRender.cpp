﻿#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Util/Utils.h"

void SRender::Update(Scene& scene)
{
    for(auto entityID : scene.reg.GetEntities<CRender,CTransform>())
    {
        CRender* render = scene.reg.GetComponent<CRender>(entityID);
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        
        if(scene.reg.HasComponent<CBoxCollider>(entityID))
        {
            CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(entityID);
            DrawSquare(transform->pos+box->offset,box->extents,render->OutlineColor,render->InsideColor);
        }
        if(scene.reg.HasComponent<CCircleCollider>(entityID))
        {
            CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(entityID);
            DrawCircle(transform->pos+circle->offset,circle->radius,16, render->OutlineColor,render->InsideColor);
        }
    }
    DrawPlayer(scene);
    DrawTank(scene);
}

void SRender::DrawPlayer(Scene& scene)
{
    for (auto element : scene.reg.GetEntities<CPlayer,CTransform,CCircleCollider>())
    {
        CTransform* playerTransform = scene.reg.GetComponent<CTransform>(element);
        CPlayer* playerComponent = scene.reg.GetComponent<CPlayer>(element);
        CCircleCollider* playerCircle = scene.reg.GetComponent<CCircleCollider>(element);
        vec2 armStart = {cosf(playerComponent->rot),sinf(playerComponent->rot)};
        vec2 armEnd = armStart;
        armStart*=playerCircle->radius;
        armEnd*=playerComponent->aimLength;
        vec3 color = {1.0f,1.0f,1.0f};
        
        auto playerState = playerComponent->state;
        if (playerState == CPlayer::States::SHOOTING)
            color = {1.0f,0.0f,0.0f};
        if (playerState==CPlayer::States::RELOADING)
            color = {1.0f,1.0f,0.0f};
        App::DrawLine(playerTransform->pos.x+armStart.x,playerTransform->pos.y+armStart.y, playerTransform->pos.x+armEnd.x,playerTransform->pos.y+armEnd.y,color.x,color.y,color.z);
    }
    
}

void SRender::DrawTank(Scene& scene)
{
    for(auto element : scene.reg.GetEntities<CEnemyTank,CTransform,CCircleCollider,CBoxCollider>())
    {
        CEnemyTank* tank = scene.reg.GetComponent<CEnemyTank>(element);
        CTransform* transform = scene.reg.GetComponent<CTransform>(element);
        CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(element);
        CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(element);
        vec2 armStart  = {cosf(tank->rot),sinf(tank->rot)};
        vec2 armEnd = armStart;
        armEnd*=tank->armLength;
        vec3 color = {1.0f,1.0f,1.0f};
        auto tankState = tank->state;
        if (tankState==CEnemyTank::TankState::SHOOTING)
            color = {1.0f,0.0f,0.0f};
        if (tankState==CEnemyTank::TankState::RELOADING)
            color = {1.0f,1.0f,0.0f};
        App::DrawLine(transform->pos.x+armStart.x+circle->offset.x,transform->pos.y+armStart.y, transform->pos.x+armEnd.x+circle->offset.x,transform->pos.y+armEnd.y,color.x,color.y,color.z);
    }
}

void SRender::DrawSquare(vec2 pos, vec2 extents, vec3 OutLinecolor,vec3 InsideColor)
{
    vec2 bottomLeft = {pos.x-extents.x,pos.y-extents.y};
    vec2 bottomRight = {pos.x+extents.x, pos.y-extents.y};
    vec2 topLeft = {pos.x-extents.x,pos.y+extents.y};
    vec2 topRight = {pos.x+extents.x, pos.y+extents.y};
    
    App::DrawLine(bottomLeft.x,bottomLeft.y, topLeft.x,topLeft.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //bottom left to top left
    App::DrawLine(topLeft.x,topLeft.y,topRight.x,topRight.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //top left to top right
    App::DrawLine(topRight.x,topRight.y, bottomRight.x,bottomRight.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //top right to bottom right
    App::DrawLine(bottomRight.x,bottomRight.y,bottomLeft.x,bottomLeft.y,OutLinecolor.x,OutLinecolor.y,OutLinecolor.z); //bottom right to bottom left
    
    App::DrawLine(bottomLeft.x,bottomLeft.y,topRight.x,topRight.y,InsideColor.x,InsideColor.y,InsideColor.z);
    App::DrawLine(bottomRight.x,bottomRight.y,topLeft.x,topLeft.y,InsideColor.x,InsideColor.y,InsideColor.z);
}

void SRender::DrawCircle(vec2 centre, float radius, int segments, vec3 Outsidecolor, vec3 Insidecolor)
{
    for (int i = 0; i < segments; i++)
    {
        float angle = Utils::Deg2Rad*360/segments;
        App::DrawLine(cosf(angle*i)*radius + centre.x, sinf(angle*i)*radius+centre.y,cosf(angle*(i+1))*radius + centre.x, sinf(angle*(i+1))*radius+centre.y,Outsidecolor.x,Outsidecolor.y,Outsidecolor.z);
        App::DrawLine(centre.x,centre.y,cosf(angle*i)*radius+centre.x,sinf(angle*i)*radius+centre.y,Insidecolor.x,Insidecolor.y,Insidecolor.z);
    }
}

