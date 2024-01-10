#include "stdafx.h"
#include "SFactory.h"

void SFactory::CreatePlayer(Scene* scene, vec2 pos, vec2 bounds)
{
    const auto m_player = scene->reg.CreateEntity();
    scene->reg.AddComponent(m_player, CPlayer());
    scene->reg.AddComponent(m_player, CTransform(pos));
    scene->reg.AddComponent(m_player, CRigidbody());
    scene->reg.AddComponent(m_player, CRender());
    scene->reg.AddComponent(m_player,CCollider());
    scene->reg.AddComponent(m_player,CBoxCollider(bounds));
}

void SFactory::CreateBox(Scene* scene, vec2 pos, vec2 bounds)
{
    const auto m_box = scene->reg.CreateEntity();
    scene->reg.AddComponent(m_box, CTransform(pos));
    scene->reg.AddComponent(m_box, CRigidbody());
    scene->reg.AddComponent(m_box, CRender());
    scene->reg.AddComponent(m_box, CCollider());
    scene->reg.AddComponent(m_box,CBoxCollider(bounds));
}

void SFactory::CreateCircle(Scene* scene, vec2 pos, float radius)
{
    const auto m_circle= scene->reg.CreateEntity();
    scene->reg.AddComponent(m_circle, CTransform(pos));
    scene->reg.AddComponent(m_circle, CRigidbody());
    scene->reg.AddComponent(m_circle, CRender());
    scene->reg.AddComponent(m_circle, CCollider());
    scene->reg.AddComponent(m_circle,CCircleCollider(radius));
}

void SFactory::CreateCamera(Scene* scene, vec2 pos)
{
    const auto camera = scene->reg.CreateEntity();
    scene->reg.AddComponent(camera, CCamera());
    scene->reg.AddComponent(camera, CTransform(pos));
}
