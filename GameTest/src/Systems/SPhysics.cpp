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
    auto tf1 = scene->reg.GetComponent<CTransform>(aID);
    auto tf2 = scene->reg.GetComponent<CTransform>(bID);
    auto box1 = scene->reg.GetComponent<CBoxCollider>(aID);
    auto box2 = scene->reg.GetComponent<CBoxCollider>(bID);
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
    auto collision = scene->reg.CreateEntity();
    scene->reg.AddComponent(collision,CCollisionEvent(aID,bID,mtv));
    return true;
}



bool SPhysics::BoxCircle(Scene* scene, Entity boxID, Entity circleID)
{
    auto tf1 = scene->reg.GetComponent<CTransform>(boxID);
    auto tf2 = scene->reg.GetComponent<CTransform>(circleID);
    auto box = scene->reg.GetComponent<CBoxCollider>(boxID);
    auto circle = scene->reg.GetComponent<CCircleCollider>(circleID);
    float x = Utils::Clamp(tf2->pos.x,tf1->pos.x-box->extents.x,tf1->pos.x+box->extents.x);
    float y = Utils::Clamp(tf2->pos.y,tf1->pos.y-box->extents.y,tf1->pos.y+box->extents.y);
    vec2 closest = {x,y};
    float distance = Utils::Distance(closest,tf2->pos);
    if(distance<circle->radius)
    {
        vec2 diff = tf2->pos-closest;
        float minDist = distance-circle->radius;
        vec2 mtv = Utils::Normalize(diff)*minDist;

        auto collision = scene->reg.CreateEntity();
        scene->reg.AddComponent(collision,CCollisionEvent(boxID,circleID,mtv));
        return true;
    }
    return false;
    
}






bool SPhysics::CircleCircle(Scene* scene, Entity aID, Entity bID)
{
    auto tf1 = scene->reg.GetComponent<CTransform>(aID);
    auto tf2 = scene->reg.GetComponent<CTransform>(bID);
    auto circle1 = scene->reg.GetComponent<CCircleCollider>(aID);
    auto circle2 = scene->reg.GetComponent<CCircleCollider>(bID);
    float distance = Utils::Distance(tf1->pos,tf2->pos);
    float radiiSum = circle1->radius + circle2->radius;
    if( distance <= radiiSum)
    {
        float minDist = distance-radiiSum;
        vec2 diff = tf2->pos-tf1->pos;
        vec2 mtv = Utils::Normalize(diff)*minDist;
        auto collision = scene->reg.CreateEntity();
        scene->reg.AddComponent(collision,CCollisionEvent(aID,bID,mtv));
        return true;
    }
    return false;
}

void SPhysics::ResolveImpulses(Scene* scene)
{
    for (auto impulse_id : scene->reg.GetEntities<CImpulseEvent>())
    {
        auto impulseEvent = scene->reg.GetComponent<CImpulseEvent>(impulse_id);
        if(scene->reg.HasComponent<CRigidbody>(impulseEvent->target))
        {
            auto rb = scene->reg.GetComponent<CRigidbody>(impulseEvent->target);
            rb->acceleration+=impulseEvent->direction*impulseEvent->force;
        }
        
    }
    scene->reg.ClearEntities<CImpulseEvent>();
}


void SPhysics::ResolveCollisions(Scene* scene)
{
    for (auto current : scene->reg.GetEntities<CCollisionEvent>())
    {
        auto collision = scene->reg.GetComponent<CCollisionEvent>(current);
        auto tfA = scene->reg.GetComponent<CTransform>(collision->entityA);
        auto tfB = scene->reg.GetComponent<CTransform>(collision->entityB);
        if(scene->reg.HasComponent<CRigidbody>(collision->entityA)&&scene->reg.HasComponent<CRigidbody>(collision->entityB))
        {
            tfA->pos = tfA->pos+(collision->mtv/2);
            tfB->pos = tfB->pos-(collision->mtv/2); 
        }
        else if(scene->reg.HasComponent<CRigidbody>(collision->entityA))
        {
            tfA->pos = tfA->pos+collision->mtv;
        }
        else if(scene->reg.HasComponent<CRigidbody>(collision->entityB))
        {
            tfB->pos = tfB->pos+collision->mtv;
        }
    }
    
    scene->reg.ClearEntities<CCollisionEvent>();
}



void SPhysics::CheckCollisions(Scene* scene)
{
    auto colliders = scene->reg.GetEntities<CCollider>();
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
    if(scene->reg.HasComponent<CBoxCollider>(a))
    {
        if(scene->reg.HasComponent<CBoxCollider>(b))
        {
            return BoxBox(scene,a,b);
        }
        if(scene->reg.HasComponent<CCircleCollider>(b))
        {
            return BoxCircle(scene,a,b);
        }
    }
    if(scene->reg.HasComponent<CCircleCollider>(a))
    {
        if(scene->reg.HasComponent<CBoxCollider>(b))
        {
            return BoxCircle(scene,b,a);
        }
        if(scene->reg.HasComponent<CCircleCollider>(b))
        {
            return CircleCircle(scene,a,b);
        }
    }
    return false;
}


void SPhysics::ApplyKinematics(Scene* scene, float dt)
{
    for(auto entityID : scene->reg.GetEntities<CRigidbody>())
    {
        CTransform* transform = scene->reg.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = scene->reg.GetComponent<CRigidbody>(entityID);
        
        rigidbody->velocity=rigidbody->velocity + rigidbody->acceleration * dt;
        transform->pos = transform->pos + rigidbody->velocity * dt;

        rigidbody->acceleration = {0,0};
    }
}


