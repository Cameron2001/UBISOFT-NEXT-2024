#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"
#include "../Components/Components.h"
#include "../Core/DeathScene.h"
#include "../Core/Factory.h"
#include "../Core/SceneManager.h"

void SPhysics::Update(Registry& Registry, float dt)
{
    DeleteOffscreen(Registry);
    CheckCollisions(Registry);
    ResolveCollisions(Registry);
    ApplyKinematics(Registry,dt);
}

bool SPhysics::BoxBox(Registry& Registry, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    if(aID == bID) return false;
    if(!Registry.HasComponent<CRigidbody>(aID) && !Registry.HasComponent<CRigidbody>(bID)) return false;
    
    CBoxCollider* box1 = Registry.GetComponent<CBoxCollider>(aID);
    CBoxCollider* box2 = Registry.GetComponent<CBoxCollider>(bID);
    vec2 pos1 = Registry.GetComponent<CTransform>(aID)->pos+box1->offset;
    vec2 pos2 = Registry.GetComponent<CTransform>(bID)->pos+box2->offset;
    vec2 diff = {pos2-pos1};
    
    auto x = (box1->extents.x+box2->extents.x) - abs(diff.x);
    auto y = (box1->extents.y+box2->extents.y) - abs(diff.y);
    if(x<=0 || y<=0)    return false;
    if (x<y)
    {
        auto sx = Utils::Sign(diff.x);
        vec2 normal = {-sx,0};
        vec2 mtv = {-x * sx,0};
        Factory::CreateCollisionEvent(Registry,aID,bID,mtv,normal);
    }
    else if (x>y)
    {
        auto sy = Utils::Sign(diff.y);
        vec2 normal = {0,-sy};
        vec2 mtv = {0,y * -sy};
        Factory::CreateCollisionEvent(Registry,aID,bID,mtv,normal);
    }
    
    
    
    
    return true;
}



bool SPhysics::BoxCircle(Registry& Registry, Entity boxID, Entity circleID)
{
    if(boxID == circleID) return false;
    if(!Registry.HasComponent<CRigidbody>(boxID) && !Registry.HasComponent<CRigidbody>(circleID)) return false;
    
    const CBoxCollider* box = Registry.GetComponent<CBoxCollider>(boxID);
    const CCircleCollider* circle = Registry.GetComponent<CCircleCollider>(circleID);
    const vec2 pos1 = Registry.GetComponent<CTransform>(boxID)->pos+box->offset;
    const vec2 pos2 = Registry.GetComponent<CTransform>(circleID)->pos+circle->offset;
    const float x = Utils::Clamp(pos2.x,pos1.x-box->extents.x,pos1.x+box->extents.x);
    const float y = Utils::Clamp(pos2.y,pos1.y-box->extents.y,pos1.y+box->extents.y);
    const vec2 closest = {x,y};
    const float distance = Utils::Distance(closest,pos2);
    if(distance<circle->radius)
    {
        const float minDist = distance-circle->radius;
        const vec2 diff = pos2-closest;
        const vec2 normal = Utils::Normalize(diff);
        const vec2 mtv = Utils::Normalize(diff)*minDist;
        Factory::CreateCollisionEvent(Registry,boxID,circleID,mtv,normal);
        return true;
    }
    return false;
    
}


bool SPhysics::CircleCircle(Registry& Registry, Entity aID, Entity bID)
{
    if(aID == bID) return false;
    if(!Registry.HasComponent<CRigidbody>(aID) && !Registry.HasComponent<CRigidbody>(bID)) return false;
    
    const CCircleCollider* circle1 = Registry.GetComponent<CCircleCollider>(aID);
    const CCircleCollider* circle2 = Registry.GetComponent<CCircleCollider>(bID);
    const vec2 pos1 = Registry.GetComponent<CTransform>(aID)->pos+circle1->offset;
    const vec2 pos2 =Registry.GetComponent<CTransform>(bID)->pos+circle2->offset;
    const float distance = Utils::Distance(pos1,pos2);
    const float radiiSum = circle1->radius + circle2->radius;
    if( distance <= radiiSum)
    {
        const float minDist = distance-radiiSum;
        const vec2 diff = pos2-pos1;
        //diff = {abs(diff.x),abs(diff.y)};
        const vec2 normal = Utils::Normalize(diff);
        const vec2 mtv = Utils::Normalize(diff)*minDist;
        Factory::CreateCollisionEvent(Registry,aID,bID,mtv,normal);
        return true;
    }
    return false;
}


void SPhysics::ResolveCollisions(Registry& Registry)
{
    for (auto current : Registry.GetEntities<CCollisionEvent>())
    {
        const CCollisionEvent* collision = Registry.GetComponent<CCollisionEvent>(current);
        CTransform* tfA = Registry.GetComponent<CTransform>(collision->entityA);
        CTransform* tfB = Registry.GetComponent<CTransform>(collision->entityB);
        if(Registry.HasComponent<CRigidbody>(collision->entityA)&&Registry.HasComponent<CRigidbody>(collision->entityB))
        {
            tfA->pos = tfA->pos+(collision->mtv/2);
            tfB->pos = tfB->pos-(collision->mtv/2);
            
            CRigidbody* bodyA = Registry.GetComponent<CRigidbody>(collision->entityA);
            CRigidbody* bodyB = Registry.GetComponent<CRigidbody>(collision->entityB);
            vec2 veloAlongNormal = bodyB->velocity-bodyA->velocity;
            vec2 projection = Utils::Project(veloAlongNormal,collision->normal);
            float e = (bodyA->elasticity+bodyB->elasticity)/2;
            

            bodyA->velocity+=projection*e;
            bodyB->velocity-=projection*e;
        }
        else if(Registry.HasComponent<CRigidbody>(collision->entityA))
        {
            CRigidbody* body = Registry.GetComponent<CRigidbody>(collision->entityA);
            vec2 projection = Utils::Project(body->velocity,collision->normal);
            tfA->pos = tfA->pos+collision->mtv;
            body->velocity-=projection*body->elasticity;
        }
        
        else if (Registry.HasComponent<CRigidbody>(collision->entityB))
        {
            CRigidbody* body = Registry.GetComponent<CRigidbody>(collision->entityB);
            vec2 projection = Utils::Project(body->velocity,collision->normal);
            tfB->pos = tfB->pos-collision->mtv;
            body->velocity-=projection*body->elasticity;
            
        }
            
        if(Registry.HasComponent<CDamage>(collision->entityA)&&Registry.HasComponent<CHealth>(collision->entityB))
        {
            const auto damge = Registry.GetComponent<CDamage>(collision->entityA);
            Factory::CreateDamageEvent(Registry,collision->entityB,damge->damage);
        }
        if(Registry.HasComponent<CDamage>(collision->entityB)&&Registry.HasComponent<CHealth>(collision->entityA))
        {
            const auto damge = Registry.GetComponent<CDamage>(collision->entityB);
            Factory::CreateDamageEvent(Registry,collision->entityA,damge->damage);
        }
    }
    
    Registry.ClearEntities<CCollisionEvent>();
}



void SPhysics::CheckCollisions(Registry& Registry)
{
    
    const std::vector<unsigned> boxes = Registry.GetEntities<CBoxCollider>();
    const std::vector<unsigned> circles = Registry.GetEntities<CCircleCollider>();
    for (size_t i =0; i< boxes.size();++i)
    {
        for(size_t j = i+1; j<boxes.size(); ++j)
        {
            BoxBox(Registry,boxes[i],boxes[j]);
        }
        for(size_t k = 0; k<circles.size(); ++k)
        {
            BoxCircle(Registry,boxes[i],circles[k]);
        }
    }
    for (size_t i =0; i< circles.size();++i)
    {
        for(size_t j = i+1; j<circles.size(); ++j)
        {
            CircleCircle(Registry,circles[i],circles[j]);
        }
    }
    
}

bool SPhysics::CheckCollision(Registry& Registry, Entity a, Entity b)
{
    if(Registry.HasComponent<CBoxCollider>(a))
    {
        if(Registry.HasComponent<CBoxCollider>(b))
        {
            return BoxBox(Registry,a,b);
        }
        if(Registry.HasComponent<CCircleCollider>(b))
        {
            return BoxCircle(Registry,a,b);
        }
    }
    if(Registry.HasComponent<CCircleCollider>(a))
    {
        if(Registry.HasComponent<CBoxCollider>(b))
        {
            return BoxCircle(Registry,b,a);
        }
        if(Registry.HasComponent<CCircleCollider>(b))
        {
            return CircleCircle(Registry,a,b);
        }
    }
    return false;
}


void SPhysics::ApplyKinematics(Registry& Registry, float dt)
{
    for(const auto entityID : Registry.GetEntities<CRigidbody>())
    {
        CTransform* transform = Registry.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = Registry.GetComponent<CRigidbody>(entityID);
        
        rigidbody->velocity+= rigidbody->acceleration * dt;
        rigidbody->velocity*=pow((1-rigidbody->drag),dt);
        transform->pos+= rigidbody->velocity * dt;

        rigidbody->acceleration = {0,0};
    }
}

void SPhysics::DeleteOffscreen(Registry& Registry)
{
    float buffer = 100.0f;
    bool death = false;
    for (auto element : Registry.GetEntities<CTransform>())
    {
        CTransform* transform = Registry.GetComponent<CTransform>(element);
        if(transform->pos.x<0-buffer||
            transform->pos.x>1024+buffer||
            transform->pos.y<0-buffer||
            transform->pos.y>768+buffer)
        {
            if(Registry.HasComponent<CHealth>(element))
            {
                Registry.GetComponent<CHealth>(element)->isDead = true;
            }
            else
            {
                Registry.DeleteEntity(element); 
            }
            
        }
    }
}


