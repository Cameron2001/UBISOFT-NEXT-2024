#include "stdafx.h"
#include "SPhysics.h"

#include "../Components/CImpulseEvent.h"
#include "../Util/Utils.h"
#include "../Components/Components.h"

void SPhysics::Update(Scene* scene, float dt)
{
    ApplyKinematics(scene,dt);
    CheckCollisions(scene);
    ResolveCollisions(scene);
    ResolveImpulses(scene);
}

bool SPhysics::BoxBox(Scene* scene, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    auto tf1 = scene->m_register.GetComponent<CTransform>(aID);
    auto tf2 = scene->m_register.GetComponent<CTransform>(bID);
    auto box1 = scene->m_register.GetComponent<CBoxCollider>(aID);
    auto box2 = scene->m_register.GetComponent<CBoxCollider>(bID);
    float xMin1 = tf1->pos.x - box1->extents.x;
    float xMax1 = tf1->pos.x + box1->extents.x;
    float yMin1 = tf1->pos.y - box1->extents.y;
    float yMax1 = tf1->pos.y + box1->extents.y;

    float xMin2 = tf2->pos.x - box2->extents.x;
    float xMax2 = tf2->pos.x + box2->extents.x;
    float yMin2 = tf2->pos.y - box2->extents.y;
    float yMax2 = tf2->pos.y + box2->extents.y;
    
    if(xMax1 < xMin2 || xMin1 > xMax2) return false;
    if(yMax1 < yMin2 || yMin1 > yMax2) return false;
    
    vec2 diff= (tf2->pos)-(tf1->pos);
   // vec2 diff= (tf2->pos+box2->extents*2)-(tf1->pos+box1->extents*2);
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
    auto collision = scene->m_register.CreateEntity();
    scene->m_register.AddComponent(collision,CCollisionEvent(aID,bID,mtv));
    return true;
}



bool SPhysics::BoxCircle(Scene* scene, Entity boxID, Entity circleID)
{
    auto tf1 = scene->m_register.GetComponent<CTransform>(boxID);
    auto tf2 = scene->m_register.GetComponent<CTransform>(circleID);
    auto box = scene->m_register.GetComponent<CBoxCollider>(boxID);
    auto circle = scene->m_register.GetComponent<CCircleCollider>(circleID);
    float x = Utils::Clamp(tf2->pos.x,tf1->pos.x-box->extents.x,tf1->pos.x+box->extents.x);
    float y = Utils::Clamp(tf2->pos.y,tf1->pos.y-box->extents.y,tf1->pos.y+box->extents.y);
    vec2 closest = {x,y};
    float distance = Utils::Distance(closest,tf2->pos);
    if(distance<circle->radius)
    {
        vec2 diff = tf2->pos-closest;
        float minDist = distance-circle->radius;
        vec2 mtv = Utils::Normalize(diff)*minDist;

        auto collision = scene->m_register.CreateEntity();
        scene->m_register.AddComponent(collision,CCollisionEvent(boxID,circleID,mtv));
        return true;
    }
    return false;
    
}






bool SPhysics::CircleCircle(Scene* scene, Entity aID, Entity bID)
{
    auto tf1 = scene->m_register.GetComponent<CTransform>(aID);
    auto tf2 = scene->m_register.GetComponent<CTransform>(bID);
    auto circle1 = scene->m_register.GetComponent<CCircleCollider>(aID);
    auto circle2 = scene->m_register.GetComponent<CCircleCollider>(bID);
    float distance = Utils::Distance(tf1->pos,tf2->pos);
    float radiiSum = circle1->radius + circle2->radius;
    if( distance <= radiiSum)
    {
        float minDist = distance-radiiSum;
        vec2 diff = tf2->pos-tf1->pos;
        vec2 mtv = Utils::Normalize(diff)*minDist;
        auto collision = scene->m_register.CreateEntity();
        scene->m_register.AddComponent(collision,CCollisionEvent(aID,bID,mtv));
        return true;
    }
    return false;
}

void SPhysics::ResolveImpulses(Scene* scene)
{
    auto impulseIDs = scene->m_register.GetEntities<CImpulseEvent>();
    for (auto impulse_id : impulseIDs)
    {
        auto impulseEvent = scene->m_register.GetComponent<CImpulseEvent>(impulse_id);
        if(scene->m_register.HasComponent<CRigidbody>(impulseEvent->target))
        {
            auto rb = scene->m_register.GetComponent<CRigidbody>(impulseEvent->target);
            rb->acceleration+=impulseEvent->direction*impulseEvent->force;
        }
        
    }
    scene->m_register.ClearEntities<CImpulseEvent>();
}


void SPhysics::ResolveCollisions(Scene* scene)
{
    auto Collisions = scene->m_register.GetEntities<CCollisionEvent>();
    for (auto current : Collisions)
    {
        auto collision = scene->m_register.GetComponent<CCollisionEvent>(current);
        auto tfA = scene->m_register.GetComponent<CTransform>(collision->entityA);
        auto tfB = scene->m_register.GetComponent<CTransform>(collision->entityB);
        if(scene->m_register.HasComponent<CRigidbody>(collision->entityA)&&scene->m_register.HasComponent<CRigidbody>(collision->entityB))
        {
            tfA->pos = tfA->pos+(collision->mtv/2);
            tfB->pos = tfB->pos-(collision->mtv/2); 
        }
        else if(scene->m_register.HasComponent<CRigidbody>(collision->entityA))
        {
            tfA->pos = tfA->pos+collision->mtv;
        }
        else if(scene->m_register.HasComponent<CRigidbody>(collision->entityB))
        {
            tfB->pos = tfB->pos+collision->mtv;
        }
    }
    
    scene->m_register.ClearEntities<CCollisionEvent>();
}



void SPhysics::CheckCollisions(Scene* scene)
{
    auto colliders = scene->m_register.GetEntities<CCollider>();
    for (size_t i =0; i< colliders.size();i++)
    {
        for(size_t j = i+1; j<colliders.size(); j++)
        {
            CheckCollision(scene, colliders[i],colliders[j]);
        }
    } 
}

bool SPhysics::CheckCollision(Scene* scene, Entity a, Entity b)
{
    if(scene->m_register.HasComponent<CBoxCollider>(a))
    {
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            return BoxBox(scene,a,b);
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            return BoxCircle(scene,a,b);
        }
    }
    if(scene->m_register.HasComponent<CCircleCollider>(a))
    {
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            return BoxCircle(scene,b,a);
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            return CircleCircle(scene,a,b);
        }
    }
    return false;
}


void SPhysics::ApplyKinematics(Scene* scene, float dt)
{
    for(auto entityID : scene->m_register.GetEntities<CRigidbody>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);
        
        rigidbody->velocity=rigidbody->velocity + rigidbody->acceleration * dt;
        transform->pos = transform->pos + rigidbody->velocity * dt;

        rigidbody->acceleration = {0,0};
    }
}


