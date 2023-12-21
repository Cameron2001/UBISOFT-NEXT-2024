#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"

void SPhysics::Update(Scene* scene, float dt)
{
    for(auto entityID : scene->m_register.GetEntities<CRigidbody>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);
        
        vec2 fa = rigidbody->force * rigidbody->invMass;
        vec2 fg = gravity*rigidbody->gravityScale;
        
        rigidbody->acceleration = fa+fg;
        rigidbody->velocity=rigidbody->velocity + rigidbody->acceleration * dt;
        transform->pos = transform->pos + rigidbody->velocity * dt;

        rigidbody->force = {0,0};
    }
}

bool SPhysics::BoxBox(CBoxCollider box1, CTransform tf1, CBoxCollider box2, CTransform tf2)
{
    if(box1.max.x < box2.min.x || box1.min.x > box2.max.x) return false;
    if(box1.max.y < box2.min.y || box1.min.y > box2.max.y) return false;
    return true;
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

void SPhysics::ResolveCollision(CRigidbody body1, CRigidbody body2)
{
}

void SPhysics::AddImpulse(vec2 direction, CRigidbody body)
{
}

void SPhysics::ApplyKinematics(float dt)
{
    
}

