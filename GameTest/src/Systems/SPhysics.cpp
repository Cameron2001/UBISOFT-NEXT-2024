#include "stdafx.h"
#include "SPhysics.h"

#include "SFactory.h"
#include "../Components/CImpulseEvent.h"
#include "../Util/Utils.h"
#include "../Components/Components.h"

void SPhysics::Update(Scene& scene, float dt)
{
    ApplyKinematics(scene,dt);
    CheckCollisions(scene);
    ResolveCollisions(scene);
    ResolveImpulses(scene);
    ResolveAngularImpulses(scene);
}

bool SPhysics::BoxBox(Scene& scene, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    CTransform* tf1 = scene.reg.GetComponent<CTransform>(aID);
    CTransform* tf2 = scene.reg.GetComponent<CTransform>(bID);
    CBoxCollider* box1 = scene.reg.GetComponent<CBoxCollider>(aID);
    CBoxCollider* box2 = scene.reg.GetComponent<CBoxCollider>(bID);
    vec2 min1 = {tf1->pos.x - box1->extents.x,tf1->pos.y - box1->extents.y};
    vec2 min2 = { tf2->pos.x - box2->extents.x,tf2->pos.y - box2->extents.y};
    vec2 max1 = {tf1->pos.x + box1->extents.x, tf1->pos.y + box1->extents.y};
    vec2 max2 = {tf2->pos.x + box2->extents.x, tf2->pos.y + box2->extents.y};
    //max1 = Utils::Rotate(max1,tf1->rot,tf1->pos);
    //max2 = Utils::Rotate(max2, tf2->rot,tf2->pos);
    //min1 = Utils::Rotate(min1,tf1->rot,tf1->pos);
    //min2 = Utils::Rotate(min2,tf2->rot,tf2->pos);
    if(max1.x < min2.x || min1.x > max2.x) return false;
    if(max1.y < min2.y || min1.y > max2.y) return false;
    
    vec2 diff= (tf2->pos)-(tf1->pos);
    vec2 mtv = {(box1->extents.x+box2->extents.x)-abs(diff.x),
        (box1->extents.y+box2->extents.y) - abs(diff.y)};
    if(mtv.x < mtv.y)
    {
        mtv.x*=-Utils::Sign(diff.x);
        mtv.y=0;
    }
    else
    {
        mtv.x = 0.0f;
        mtv.y*=-Utils::Sign(diff.y);
    }
    scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv);
    return true;
}



bool SPhysics::BoxCircle(Scene& scene, Entity boxID, Entity circleID)
{
    CTransform* tf1 = scene.reg.GetComponent<CTransform>(boxID);
    CTransform* tf2 = scene.reg.GetComponent<CTransform>(circleID);
    CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(boxID);
    CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(circleID);
    float x = Utils::Clamp(tf2->pos.x,tf1->pos.x-box->extents.x,tf1->pos.x+box->extents.x);
    float y = Utils::Clamp(tf2->pos.y,tf1->pos.y-box->extents.y,tf1->pos.y+box->extents.y);
    vec2 closest = {x,y};
    float distance = Utils::Distance(closest,tf2->pos);
    if(distance<circle->radius)
    {
        vec2 diff = tf2->pos-closest;
        float minDist = distance-circle->radius;
        vec2 mtv = Utils::Normalize(diff)*minDist;

        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,boxID,circleID,mtv);
        return true;
    }
    return false;
    
}






bool SPhysics::CircleCircle(Scene& scene, Entity aID, Entity bID)
{
    CTransform* tf1 = scene.reg.GetComponent<CTransform>(aID);
    CTransform* tf2 = scene.reg.GetComponent<CTransform>(bID);
    CCircleCollider* circle1 = scene.reg.GetComponent<CCircleCollider>(aID);
    CCircleCollider* circle2 = scene.reg.GetComponent<CCircleCollider>(bID);
    float distance = Utils::Distance(tf1->pos,tf2->pos);
    float radiiSum = circle1->radius + circle2->radius;
    if( distance <= radiiSum)
    {
        float minDist = distance-radiiSum;
        vec2 diff = tf2->pos-tf1->pos;
        vec2 mtv = Utils::Normalize(diff)*minDist;

        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv);
        return true;
    }
    return false;
}

void SPhysics::ResolveImpulses(Scene& scene)
{
    for (auto impulse_id : scene.reg.GetEntities<CImpulseEvent>())
    {
        auto impulseEvent = scene.reg.GetComponent<CImpulseEvent>(impulse_id);
        if(scene.reg.HasComponent<CRigidbody>(impulseEvent->target))
        {
            CRigidbody* rb = scene.reg.GetComponent<CRigidbody>(impulseEvent->target);
            rb->acceleration+=impulseEvent->direction*impulseEvent->force;
        }
        
    }
    scene.reg.ClearEntities<CImpulseEvent>();
}

void SPhysics::ResolveAngularImpulses(Scene& scene)
{
    for (auto impulse_id : scene.reg.GetEntities<CAngularImpulseEvent>())
    {
        CAngularImpulseEvent* impulseEvent = scene.reg.GetComponent<CAngularImpulseEvent>(impulse_id);
        if(scene.reg.HasComponent<CRigidbody>(impulseEvent->target))
        {
            CRigidbody* rb = scene.reg.GetComponent<CRigidbody>(impulseEvent->target);
            rb->angularAcceleration+=impulseEvent->force;
        }
    }
    scene.reg.ClearEntities<CAngularImpulseEvent>();
}


void SPhysics::ResolveCollisions(Scene& scene)
{
    for (auto current : scene.reg.GetEntities<CCollisionEvent>())
    {
        CCollisionEvent* collision = scene.reg.GetComponent<CCollisionEvent>(current);
        CTransform* tfA = scene.reg.GetComponent<CTransform>(collision->entityA);
        CTransform* tfB = scene.reg.GetComponent<CTransform>(collision->entityB);
        if(scene.reg.HasComponent<CRigidbody>(collision->entityA)&&scene.reg.HasComponent<CRigidbody>(collision->entityB))
        {
            tfA->pos = tfA->pos+(collision->mtv/2);
            tfB->pos = tfB->pos-(collision->mtv/2); 
        }
        else if(scene.reg.HasComponent<CRigidbody>(collision->entityA))
        {
            tfA->pos = tfA->pos+collision->mtv;
        }
        else if(scene.reg.HasComponent<CRigidbody>(collision->entityB))
        {
            tfB->pos = tfB->pos+collision->mtv;
        }
        if(scene.reg.HasComponent<CDamage>(collision->entityA)&&scene.reg.HasComponent<CHealth>(collision->entityB))
        {
            auto damge = scene.reg.GetComponent<CDamage>(collision->entityA);
            scene.reg.GetSystem<SFactory>()->CreateDamageEvent(scene,collision->entityB,damge->damage);
        }
        if(scene.reg.HasComponent<CDamage>(collision->entityB)&&scene.reg.HasComponent<CHealth>(collision->entityA))
        {
            auto damge = scene.reg.GetComponent<CDamage>(collision->entityB);
            scene.reg.GetSystem<SFactory>()->CreateDamageEvent(scene,collision->entityA,damge->damage);
        }
    }
    
    scene.reg.ClearEntities<CCollisionEvent>();
}



void SPhysics::CheckCollisions(Scene& scene)
{
    const std::vector<unsigned> colliders = scene.reg.GetEntities<CCollider>();
    for (size_t i =0; i< colliders.size();i++)
    {
        for(size_t j = i+1; j<colliders.size(); j++)
        {
            CheckCollision(scene, colliders[i],colliders[j]);
        }
    } 
}

bool SPhysics::CheckCollision(Scene& scene, Entity a, Entity b)
{
    if(scene.reg.HasComponent<CBoxCollider>(a))
    {
        if(scene.reg.HasComponent<CBoxCollider>(b))
        {
            return BoxBox(scene,a,b);
        }
        if(scene.reg.HasComponent<CCircleCollider>(b))
        {
            return BoxCircle(scene,a,b);
        }
    }
    if(scene.reg.HasComponent<CCircleCollider>(a))
    {
        if(scene.reg.HasComponent<CBoxCollider>(b))
        {
            return BoxCircle(scene,b,a);
        }
        if(scene.reg.HasComponent<CCircleCollider>(b))
        {
            return CircleCircle(scene,a,b);
        }
    }
    return false;
}


void SPhysics::ApplyKinematics(Scene& scene, float dt)
{
    for(auto entityID : scene.reg.GetEntities<CRigidbody>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = scene.reg.GetComponent<CRigidbody>(entityID);
        
        rigidbody->velocity+= rigidbody->acceleration * dt;
        rigidbody->velocity*=pow((1-rigidbody->drag),dt);
        transform->pos+= rigidbody->velocity * dt;

        rigidbody->angularVelocity+=rigidbody->angularAcceleration*dt;
        rigidbody->angularVelocity*=pow((1-rigidbody->angularDrag),dt);
        transform->rot+= rigidbody->angularVelocity * dt;

        rigidbody->acceleration = {0,0};
        rigidbody->angularAcceleration = 0;
    }
}


