#include "stdafx.h"
#include "SPhysics.h"

void SPhysics::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CRigidbody>())
    {
        CTransform transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRigidbody rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);
    }
}

void SPhysics::UpdateCollision()
{
}

void SPhysics::ResolveCollision()
{
}

void SPhysics::CollisionResponse()
{
}

void SPhysics::UpdatePosition()
{
}

void SPhysics::addImpulse(vec2 direction, CRigidbody body)
{
}

bool SPhysics::IsColliding()
{
    return true;
}
