#include "stdafx.h"
#include "SPhysics.h"

#include "SFactory.h"
#include "../Util/Utils.h"
#include "../Components/Components.h"

void SPhysics::Update(Scene& scene, float dt)
{
    DeleteOffscreen(scene);
    CheckCollisions(scene);
    ResolveCollisions(scene);
    ApplyKinematics(scene,dt);
}

bool SPhysics::BoxBox(Scene& scene, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    if(aID == bID) return false;
    if(!scene.reg.HasComponent<CRigidbody>(aID) && !scene.reg.HasComponent<CRigidbody>(bID)) return false;
    
    CBoxCollider* box1 = scene.reg.GetComponent<CBoxCollider>(aID);
    CBoxCollider* box2 = scene.reg.GetComponent<CBoxCollider>(bID);
    vec2 pos1 = scene.reg.GetComponent<CTransform>(aID)->pos+box1->offset;
    vec2 pos2 = scene.reg.GetComponent<CTransform>(bID)->pos+box2->offset;
    vec2 diff = {pos2-pos1};
    
    auto x = (box1->extents.x+box2->extents.x) - abs(diff.x);
    auto y = (box1->extents.y+box2->extents.y) - abs(diff.y);
    if(x<=0 || y<=0)    return false;
    if (x<y)
    {
        auto sx = Utils::Sign(diff.x);
        vec2 normal = {-sx,0};
        vec2 mtv = {-x * sx,0};
        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv,normal);
    }
    else if (x>y)
    {
        auto sy = Utils::Sign(diff.y);
        vec2 normal = {0,-sy};
        vec2 mtv = {0,y * -sy};
        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv,normal);
    }
    
    
    
    
    return true;
}



bool SPhysics::BoxCircle(Scene& scene, Entity boxID, Entity circleID)
{
    if(boxID == circleID) return false;
    if(!scene.reg.HasComponent<CRigidbody>(boxID) && !scene.reg.HasComponent<CRigidbody>(circleID)) return false;
    
    const CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(boxID);
    const CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(circleID);
    const vec2 pos1 = scene.reg.GetComponent<CTransform>(boxID)->pos+box->offset;
    const vec2 pos2 = scene.reg.GetComponent<CTransform>(circleID)->pos+circle->offset;
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
        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,boxID,circleID,mtv,normal);
        return true;
    }
    return false;
    
}


bool SPhysics::CircleCircle(Scene& scene, Entity aID, Entity bID)
{
    if(aID == bID) return false;
    if(!scene.reg.HasComponent<CRigidbody>(aID) && !scene.reg.HasComponent<CRigidbody>(bID)) return false;
    
    const CCircleCollider* circle1 = scene.reg.GetComponent<CCircleCollider>(aID);
    const CCircleCollider* circle2 = scene.reg.GetComponent<CCircleCollider>(bID);
    const vec2 pos1 = scene.reg.GetComponent<CTransform>(aID)->pos+circle1->offset;
    const vec2 pos2 =scene.reg.GetComponent<CTransform>(bID)->pos+circle2->offset;
    const float distance = Utils::Distance(pos1,pos2);
    const float radiiSum = circle1->radius + circle2->radius;
    if( distance <= radiiSum)
    {
        const float minDist = distance-radiiSum;
        const vec2 diff = pos2-pos1;
        //diff = {abs(diff.x),abs(diff.y)};
        const vec2 normal = Utils::Normalize(diff);
        const vec2 mtv = Utils::Normalize(diff)*minDist;
        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv,normal);
        return true;
    }
    return false;
}


void SPhysics::ResolveCollisions(Scene& scene)
{
    for (auto current : scene.reg.GetEntities<CCollisionEvent>())
    {
        const CCollisionEvent* collision = scene.reg.GetComponent<CCollisionEvent>(current);
        CTransform* tfA = scene.reg.GetComponent<CTransform>(collision->entityA);
        CTransform* tfB = scene.reg.GetComponent<CTransform>(collision->entityB);
        if(scene.reg.HasComponent<CRigidbody>(collision->entityA)&&scene.reg.HasComponent<CRigidbody>(collision->entityB))
        {
            tfA->pos = tfA->pos+(collision->mtv/2);
            tfB->pos = tfB->pos-(collision->mtv/2);
            
            CRigidbody* bodyA = scene.reg.GetComponent<CRigidbody>(collision->entityA);
            CRigidbody* bodyB = scene.reg.GetComponent<CRigidbody>(collision->entityB);
            vec2 veloAlongNormal = bodyB->velocity-bodyA->velocity;
            vec2 projection = Utils::Project(veloAlongNormal,collision->normal);
            float e = (bodyA->elasticity+bodyB->elasticity)/2;
            

            bodyA->velocity+=projection*e;
            bodyB->velocity-=projection*e;
        }
        else if(scene.reg.HasComponent<CRigidbody>(collision->entityA))
        {
            CRigidbody* body = scene.reg.GetComponent<CRigidbody>(collision->entityA);
            vec2 projection = Utils::Project(body->velocity,collision->normal);
            tfA->pos = tfA->pos+collision->mtv;
            body->velocity-=projection*body->elasticity;
        }
        
        else if (scene.reg.HasComponent<CRigidbody>(collision->entityB))
        {
            CRigidbody* body = scene.reg.GetComponent<CRigidbody>(collision->entityB);
            vec2 projection = Utils::Project(body->velocity,collision->normal);
            tfB->pos = tfB->pos-collision->mtv;
            body->velocity-=projection*body->elasticity;
            
        }
            
        if(scene.reg.HasComponent<CDamage>(collision->entityA)&&scene.reg.HasComponent<CHealth>(collision->entityB))
        {
            const auto damge = scene.reg.GetComponent<CDamage>(collision->entityA);
            scene.reg.GetSystem<SFactory>()->CreateDamageEvent(scene,collision->entityB,damge->damage);
        }
        if(scene.reg.HasComponent<CDamage>(collision->entityB)&&scene.reg.HasComponent<CHealth>(collision->entityA))
        {
            const auto damge = scene.reg.GetComponent<CDamage>(collision->entityB);
            scene.reg.GetSystem<SFactory>()->CreateDamageEvent(scene,collision->entityA,damge->damage);
        }
    }
    
    scene.reg.ClearEntities<CCollisionEvent>();
}



void SPhysics::CheckCollisions(Scene& scene)
{
    
    const std::vector<unsigned> boxes = scene.reg.GetEntities<CBoxCollider>();
    const std::vector<unsigned> circles = scene.reg.GetEntities<CCircleCollider>();
    for (size_t i =0; i< boxes.size();++i)
    {
        for(size_t j = i+1; j<boxes.size(); ++j)
        {
            BoxBox(scene,boxes[i],boxes[j]);
        }
        for(size_t k = 0; k<circles.size(); ++k)
        {
            BoxCircle(scene,boxes[i],circles[k]);
        }
    }
    for (size_t i =0; i< circles.size();++i)
    {
        for(size_t j = i+1; j<circles.size(); ++j)
        {
            CircleCircle(scene,circles[i],circles[j]);
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
    for(const auto entityID : scene.reg.GetEntities<CRigidbody>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        CRigidbody* rigidbody = scene.reg.GetComponent<CRigidbody>(entityID);
        
        rigidbody->velocity+= rigidbody->acceleration * dt;
        rigidbody->velocity*=pow((1-rigidbody->drag),dt);
        transform->pos+= rigidbody->velocity * dt;

        rigidbody->acceleration = {0,0};
    }
}

void SPhysics::DeleteOffscreen(Scene& scene)
{
    float buffer = 100.0f;
    for (auto element : scene.reg.GetEntities<CTransform>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(element);
        if(transform->pos.x<0-buffer||
            transform->pos.x>1024+buffer||
            transform->pos.y<0-buffer||
            transform->pos.y>768+buffer)
        {
            scene.reg.DeleteEntity(element);
        }
    }
}


