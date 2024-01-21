#include "stdafx.h"
#include "SRender.h"

#include "../../App/app.h"
#include "../Components/Components.h"

void SRender::update(Registry& registry)
{
    drawShapes(registry);
    drawLabels(registry);
    drawArms(registry);
}

void SRender::drawShapes(Registry& registry)
{
    for(auto entityID : registry.getEntities<CRender>())
    {
        const CRender& render = registry.getComponent<CRender>(entityID);
        const CTransform& transform = registry.getComponent<CTransform>(entityID);
        
        if(registry.hasComponent<CBoxCollider>(entityID))
        {
            const CBoxCollider& box = registry.getComponent<CBoxCollider>(entityID);
            drawSquare(transform.pos+box.offset,box.extents,render.color);
        }
        if(registry.hasComponent<CCircleCollider>(entityID))
        {
            const CCircleCollider& circle = registry.getComponent<CCircleCollider>(entityID);
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

void SRender::drawLabels(Registry& registry)
{
    for (const auto current : registry.getEntities<CLabel>())
    {
        const CRender& render = registry.getComponent<CRender>(current);
        const CLabel& label = registry.getComponent<CLabel>(current);
        const CTransform& transform = registry.getComponent<CTransform>(current);
        App::Print(transform.pos.x+label.labelOffset.x,transform.pos.y+label.labelOffset.y,label.labelText.c_str(),render.color.x,render.color.y,render.color.z);
    }
}

void SRender::drawArms(Registry& registry)
{
    for (auto element : registry.getEntities<CArm>())
    {
        CArm& arm = registry.getComponent<CArm>(element);
        CCircleCollider& circle = registry.getComponent<CCircleCollider>(element);
        CTransform& transform = registry.getComponent<CTransform>(element);
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



