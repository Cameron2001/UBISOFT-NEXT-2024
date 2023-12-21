#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"

void SPhysics::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CRigidbody>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);
    }
}

bool SPhysics::BoxBox(CBoxCollider box1, CTransform tf1, CBoxCollider box2, CTransform tf2)
{
    return false;
}

bool SPhysics::BoxCircle(CBoxCollider box, CTransform tf1, CCircleCollider circle, CTransform tf2)
{return false;
}

bool SPhysics::BoxCapsule(CBoxCollider box, CTransform tf1, CCapsuleCollider capsule, CTransform tf2)
{
    return false;
}

bool SPhysics::BoxPlane(CBoxCollider box, CTransform tf1, CPlaneCollider plane, CTransform tf2)
{
    return false;
}

bool SPhysics::CircleCircle(CCircleCollider circle1, CTransform tf1, CCircleCollider circle2, CTransform tf2)
{
    float distance = Utils::Distance(tf1.pos,tf2.pos);
    float radiiSum = circle1.radius + circle2.radius;
    bool collision = distance <= radiiSum;
    //stuff here
    return collision;
}

bool SPhysics::CircleCapsule(CCircleCollider circle, CTransform tf1, CCapsuleCollider capsule, CTransform tf2)
{
    return false;
}

bool SPhysics::CirclePlane(CCircleCollider circle, CTransform tf1, CPlaneCollider plane, CTransform tf2)
{
    return false;
}

bool SPhysics::CapsuleCapsule(CCapsuleCollider capsule1, CTransform tf1, CCapsuleCollider capsule2, CTransform tf2)
{
    return false;
}

bool SPhysics::CapsulePlane(CCapsuleCollider capsule, CTransform tf1, CPlaneCollider plane, CTransform tf2)
{
    return false;
}

void SPhysics::addImpulse(vec2 direction, CRigidbody body)
{
}

