﻿//------------------------------------------------------------------------
// SRender.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "SRender.h"
//------------------------------------------------------------------------
#include "../../App/app.h"
#include "../Components/Components.h"
//------------------------------------------------------------------------

void SRender::update(Registry& registry)
{
    drawShapes(registry);
    drawLabels(registry);
    drawArms(registry);
}

void SRender::drawShapes(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CRender>())
    {
        const CRender& render = registry.getComponent<CRender>(ID);
        const CTransform& transform = registry.getComponent<CTransform>(ID);

        if (registry.hasComponent<CBoxCollider>(ID))
        {
            const CBoxCollider& box = registry.getComponent<CBoxCollider>(ID);
            drawSquare(transform.pos + box.offset, box.extents, render.color);
        }

        if (registry.hasComponent<CCircleCollider>(ID))
        {
            const CCircleCollider& circle = registry.getComponent<CCircleCollider>(ID);
            drawCircle(transform.pos + circle.offset, circle.radius, circle.segments, render.color);
        }
    }
}

void SRender::drawSquare(const vec2 pos, const vec2 extents, const vec3 color)
{
    const vec2 bottomLeft = {pos.x - extents.x, pos.y - extents.y};
    const vec2 bottomRight = {pos.x + extents.x, pos.y - extents.y};
    const vec2 topLeft = {pos.x - extents.x, pos.y + extents.y};
    const vec2 topRight = {pos.x + extents.x, pos.y + extents.y};

    App::DrawLine(bottomLeft.x, bottomLeft.y, topLeft.x, topLeft.y, color.x, color.y, color.z);
    //bottom left to top left
    App::DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, color.x, color.y, color.z); //top left to top right
    App::DrawLine(topRight.x, topRight.y, bottomRight.x, bottomRight.y, color.x, color.y, color.z);
    //top right to bottom right
    App::DrawLine(bottomRight.x, bottomRight.y, bottomLeft.x, bottomLeft.y, color.x, color.y, color.z);
    //bottom right to bottom left
}

void SRender::drawCircle(const vec2 centre, const float radius, const int segments, const vec3 color)
{
    for (int i = 0; i < segments; i++)
    {
        const float angle = utils::deg2Rad * 360.0f / segments;
        App::DrawLine(cosf(angle * i) * radius + centre.x, sinf(angle * i) * radius + centre.y,
                      cosf(angle * (i + 1)) * radius + centre.x, sinf(angle * (i + 1)) * radius + centre.y, color.x,
                      color.y, color.z);
    }
}

void SRender::drawLabels(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CLabel>())
    {
        const CRender& render = registry.getComponent<CRender>(ID);
        const CLabel& label = registry.getComponent<CLabel>(ID);
        const CTransform& transform = registry.getComponent<CTransform>(ID);

        App::Print(transform.pos.x + label.offset.x, transform.pos.y + label.offset.y, label.text.c_str(),
                   render.color.x, render.color.y, render.color.z);
    }
}

void SRender::drawArms(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CArm>())
    {
        const CCircleCollider& circle = registry.getComponent<CCircleCollider>(ID);
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        const CArm& arm = registry.getComponent<CArm>(ID);

        const vec2 armStart = {cosf(arm.rotation), sinf(arm.rotation)};
        const vec2 armEnd = armStart * arm.armLength;

        vec3 color = {1.0f, 1.0f, 1.0f};
        if (arm.state == CArm::ArmState::SHOOTING)
            color = {1.0f, 0.0f, 0.0f};
        if (arm.state == CArm::ArmState::RELOADING)
            color = {1.0f, 1.0f, 0.0f};
        App::DrawLine(transform.pos.x + armStart.x + circle.offset.x, transform.pos.y + armStart.y,
                      transform.pos.x + armEnd.x + circle.offset.x, transform.pos.y + armEnd.y, color.x, color.y,
                      color.z);
    }
}
