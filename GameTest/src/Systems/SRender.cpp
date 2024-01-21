#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Util/Utils.h"

void SRender::update(Registry& Registry)
{
    drawShapes(Registry);
    drawLabels(Registry);
    drawArms(Registry);
}

void SRender::drawShapes(Registry& Registry)
{
    for(auto entityID : Registry.getEntities<CRender>())
    {
        const CRender& render = Registry.getComponent<CRender>(entityID);
        const CTransform& transform = Registry.getComponent<CTransform>(entityID);
        
        if(Registry.hasComponent<CBoxCollider>(entityID))
        {
            const CBoxCollider& box = Registry.getComponent<CBoxCollider>(entityID);
            drawSquare(transform.pos+box.offset,box.extents,render.color);
        }
        if(Registry.hasComponent<CCircleCollider>(entityID))
        {
            const CCircleCollider& circle = Registry.getComponent<CCircleCollider>(entityID);
            drawCircle(transform.pos+circle.offset,circle.radius,circle.segments, render.color);
        }
    }
}

void SRender::drawSquare(vec2 pos, vec2 extents, vec3 OutLinecolor)
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

void SRender::drawCircle(vec2 centre, float radius, int segments, vec3 Outsidecolor)
{
    for (int i = 0; i < segments; i++)
    {
        const float angle = Utils::Deg2Rad*360/segments;
        App::DrawLine(cosf(angle*i)*radius + centre.x, sinf(angle*i)*radius+centre.y,cosf(angle*(i+1))*radius + centre.x, sinf(angle*(i+1))*radius+centre.y,Outsidecolor.x,Outsidecolor.y,Outsidecolor.z);
    }
}

void SRender::drawLabels(Registry& Registry)
{
    for (const auto current : Registry.getEntities<CLabel>())
    {
        const CRender& render = Registry.getComponent<CRender>(current);
        const CLabel& label = Registry.getComponent<CLabel>(current);
        const CTransform& transform = Registry.getComponent<CTransform>(current);
        App::Print(transform.pos.x+label.labelOffset.x,transform.pos.y+label.labelOffset.y,label.labelText.c_str(),render.color.x,render.color.y,render.color.z);
    }
}

void SRender::drawArms(Registry& Registry)
{
    for (auto element : Registry.getEntities<CArm>())
    {
        CArm& arm = Registry.getComponent<CArm>(element);
        CCircleCollider& circle = Registry.getComponent<CCircleCollider>(element);
        CTransform& transform = Registry.getComponent<CTransform>(element);
        vec2 armStart  = {cosf(arm.rotation),sinf(arm.rotation)};
        vec2 armEnd = armStart*arm.length;
        vec3 color = {1.0f,1.0f,1.0f};
        if (arm.state==CArm::ArmState::SHOOTING)
            color = {1.0f,0.0f,0.0f};
        if (arm.state== CArm::ArmState::RELOADING)
            color = {1.0f,1.0f,0.0f};
        App::DrawLine(transform.pos.x+armStart.x+circle.offset.x,transform.pos.y+armStart.y, transform.pos.x+armEnd.x+circle.offset.x,transform.pos.y+armEnd.y,color.x,color.y,color.z);
    }
}



