#include "stdafx.h"
#include "SPhysics.h"

#include "SFactory.h"
#include "../Util/Utils.h"
#include "../Components/Components.h"

void SPhysics::Update(Scene& scene, float dt)
{
    CheckCollisions(scene);
    ResolveCollisions(scene);
    ApplyKinematics(scene,dt);
}

bool SPhysics::BoxBox(Scene& scene, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    CBoxCollider* box1 = scene.reg.GetComponent<CBoxCollider>(aID);
    CBoxCollider* box2 = scene.reg.GetComponent<CBoxCollider>(bID);
    vec2 pos1 = scene.reg.GetComponent<CTransform>(aID)->pos+box1->offset;
    vec2 pos2 = scene.reg.GetComponent<CTransform>(bID)->pos+box2->offset;
    vec2 diff = {pos2-pos1};
    vec2 normal;
    vec2 mtv;
    auto x = (box1->extents.x+box2->extents.x) - abs(diff.x);
    auto y = (box1->extents.y+box2->extents.y) - abs(diff.y);
    if(x<=0 || y<=0)    return false;
    if (x<y)
    {
        auto sx = Utils::Sign(diff.x);
        normal = {-sx,0};
        mtv = {-x * sx,0};
    }
    else
    {
        auto sy = Utils::Sign(diff.y);
        normal = {0,-sy};
        mtv = {0,y * -sy};
    }
    scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv,normal);
    
    
    
    return true;
}



bool SPhysics::BoxCircle(Scene& scene, Entity boxID, Entity circleID)
{
    CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(boxID);
    CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(circleID);
    vec2 pos1 = scene.reg.GetComponent<CTransform>(boxID)->pos+box->offset;
    vec2 pos2 = scene.reg.GetComponent<CTransform>(circleID)->pos+circle->offset;
    float x = Utils::Clamp(pos2.x,pos1.x-box->extents.x,pos1.x+box->extents.x);
    float y = Utils::Clamp(pos2.y,pos1.y-box->extents.y,pos1.y+box->extents.y);
    vec2 closest = {x,y};
    float distance = Utils::Distance(closest,pos2);
    if(distance<circle->radius)
    {
        float minDist = distance-circle->radius;
        vec2 diff = pos2-closest;
        vec2 normal = Utils::Normalize(diff);
        vec2 mtv = Utils::Normalize(diff)*minDist;
        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,boxID,circleID,mtv,normal);
        return true;
    }
    return false;
    
}


bool SPhysics::CircleCircle(Scene& scene, Entity aID, Entity bID)
{
    
    CCircleCollider* circle1 = scene.reg.GetComponent<CCircleCollider>(aID);
    CCircleCollider* circle2 = scene.reg.GetComponent<CCircleCollider>(bID);
    vec2 pos1 = scene.reg.GetComponent<CTransform>(aID)->pos+circle1->offset;
    vec2 pos2 =scene.reg.GetComponent<CTransform>(bID)->pos+circle2->offset;
    float distance = Utils::Distance(pos1,pos2);
    float radiiSum = circle1->radius + circle2->radius;
    if( distance <= radiiSum)
    {
        float minDist = distance-radiiSum;
        vec2 diff = pos2-pos1;
        //diff = {abs(diff.x),abs(diff.y)};
        vec2 normal = Utils::Normalize(diff);
        vec2 mtv = Utils::Normalize(diff)*minDist;
        scene.reg.GetSystem<SFactory>()->CreateCollisionEvent(scene,aID,bID,mtv,normal);
        return true;
    }
    return false;
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
            CRigidbody* bodyA = scene.reg.GetComponent<CRigidbody>(collision->entityA);
            CRigidbody* bodyB = scene.reg.GetComponent<CRigidbody>(collision->entityB);
            vec2 veloAlongNormal = bodyB->velocity-bodyA->velocity;
            vec2 projection = Utils::Project(veloAlongNormal,collision->normal);
            
            tfA->pos = tfA->pos+(collision->mtv/2);
            tfB->pos = tfB->pos-(collision->mtv/2);

            bodyA->velocity+=projection*1.5;
            bodyB->velocity-=projection*1.5;
        }
        else if(scene.reg.HasComponent<CRigidbody>(collision->entityA))
        {
            CRigidbody* body = scene.reg.GetComponent<CRigidbody>(collision->entityA);
            vec2 projection = Utils::Project(body->velocity,collision->normal);
            tfA->pos = tfA->pos+collision->mtv;
            body->velocity-=projection*1.5;
        }
        
        else if (scene.reg.HasComponent<CRigidbody>(collision->entityB))
        {
            CRigidbody* body = scene.reg.GetComponent<CRigidbody>(collision->entityB);
            vec2 projection = Utils::Project(body->velocity,collision->normal);
            tfB->pos = tfB->pos-collision->mtv;
            body->velocity-=projection*1.5;
            
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
    
    /*const std::vector<unsigned> rb = scene.reg.GetEntities<CRigidbody>();
    const std::vector<unsigned> colliders = scene.reg.GetEntities<CCollider>();
    for (size_t i = 0; i<rb.size();i++)
    {
        
        for(size_t j = 0; j<colliders.size(); j++)
        {
            if(rb[i]!=colliders[i])
                CheckCollision(scene, rb[i],colliders[j]);
        }
    }*/
    /*for (size_t i =0; i< colliders.size();i++)
    {
        for(size_t j = i+1; j<colliders.size(); j++)
        {
            CheckCollision(scene, colliders[i],colliders[j]);
        }
    } */
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

        rigidbody->acceleration = {0,0};
    }
}


