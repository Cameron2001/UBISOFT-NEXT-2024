﻿#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"
#include "../Components/Components.h"
#include "../Core/DeathScene.h"
#include "../Core/Factory.h"
#include "../Core/SceneManager.h"

void SPhysics::update(Registry& registry, float dt)
{
    deleteOffscreen(registry);
    checkCollisions(registry);
    resolveCollisions(registry);
    applyKinematics(registry,dt);
}

bool SPhysics::boxBox(Registry& registry, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    if(aID == bID) return false;
    if(!registry.hasComponent<CRigidbody>(aID) && !registry.hasComponent<CRigidbody>(bID)) return false;
    
    CBoxCollider& box1 = registry.getComponent<CBoxCollider>(aID);
    CBoxCollider& box2 = registry.getComponent<CBoxCollider>(bID);
    vec2 pos1 = registry.getComponent<CTransform>(aID).pos+box1.offset;
    vec2 pos2 = registry.getComponent<CTransform>(bID).pos+box2.offset;
    vec2 diff = {pos2-pos1};
    
    auto x = (box1.extents.x+box2.extents.x) - abs(diff.x);
    auto y = (box1.extents.y+box2.extents.y) - abs(diff.y);
    if(x<=0 || y<=0)    return false;
    if (x<y)
    {
        auto sx = Utils::Sign(diff.x);
        vec2 normal = {-sx,0};
        vec2 mtv = {-x * sx,0};
        Factory::createCollisionEvent(registry,aID,bID,mtv,normal);
    }
    else if (x>y)
    {
        auto sy = Utils::Sign(diff.y);
        vec2 normal = {0,-sy};
        vec2 mtv = {0,y * -sy};
        Factory::createCollisionEvent(registry,aID,bID,mtv,normal);
    }
    
    
    
    
    return true;
}



bool SPhysics::boxCircle(Registry& registry, Entity boxID, Entity circleID)
{
    if(boxID == circleID) return false;
    if(!registry.hasComponent<CRigidbody>(boxID) && !registry.hasComponent<CRigidbody>(circleID)) return false;
    
    const CBoxCollider& box = registry.getComponent<CBoxCollider>(boxID);
    const CCircleCollider& circle = registry.getComponent<CCircleCollider>(circleID);
    const vec2 pos1 = registry.getComponent<CTransform>(boxID).pos+box.offset;
    const vec2 pos2 = registry.getComponent<CTransform>(circleID).pos+circle.offset;
    const float x = Utils::Clamp(pos2.x,pos1.x-box.extents.x,pos1.x+box.extents.x);
    const float y = Utils::Clamp(pos2.y,pos1.y-box.extents.y,pos1.y+box.extents.y);
    const vec2 closest = {x,y};
    const float distance = Utils::Distance(closest,pos2);
    if(distance<circle.radius)
    {
        const float minDist = distance-circle.radius;
        const vec2 diff = pos2-closest;
        const vec2 normal = Utils::Normalize(diff);
        const vec2 mtv = Utils::Normalize(diff)*minDist;
        Factory::createCollisionEvent(registry,boxID,circleID,mtv,normal);
        return true;
    }
    return false;
    
}


bool SPhysics::circleCircle(Registry& registry, Entity aID, Entity bID)
{
    if(aID == bID) return false;
    if(!registry.hasComponent<CRigidbody>(aID) && !registry.hasComponent<CRigidbody>(bID)) return false;
    
    const CCircleCollider& circle1 = registry.getComponent<CCircleCollider>(aID);
    const CCircleCollider& circle2 = registry.getComponent<CCircleCollider>(bID);
    const vec2 pos1 = registry.getComponent<CTransform>(aID).pos+circle1.offset;
    const vec2 pos2 =registry.getComponent<CTransform>(bID).pos+circle2.offset;
    const float distance = Utils::Distance(pos1,pos2);
    const float radiiSum = circle1.radius + circle2.radius;
    if( distance <= radiiSum)
    {
        const float minDist = distance-radiiSum;
        const vec2 diff = pos2-pos1;
        //diff = {abs(diff.x),abs(diff.y)};
        const vec2 normal = Utils::Normalize(diff);
        const vec2 mtv = Utils::Normalize(diff)*minDist;
        Factory::createCollisionEvent(registry,aID,bID,mtv,normal);
        return true;
    }
    return false;
}


void SPhysics::resolveCollisions(Registry& registry)
{
    for (auto current : registry.getEntities<CCollisionEvent>())
    {
        const CCollisionEvent& collision = registry.getComponent<CCollisionEvent>(current);
        CTransform& tfA = registry.getComponent<CTransform>(collision.entityA);
        CTransform& tfB = registry.getComponent<CTransform>(collision.entityB);
        if(registry.hasComponent<CRigidbody>(collision.entityA)&&registry.hasComponent<CRigidbody>(collision.entityB))
        {
            tfA.pos = tfA.pos+(collision.mtv/2);
            tfB.pos = tfB.pos-(collision.mtv/2);
            
            CRigidbody& bodyA = registry.getComponent<CRigidbody>(collision.entityA);
            CRigidbody& bodyB = registry.getComponent<CRigidbody>(collision.entityB);
            vec2 veloAlongNormal = bodyB.velocity-bodyA.velocity;
            vec2 projection = Utils::Project(veloAlongNormal,collision.normal);
            float e = (bodyA.elasticity+bodyB.elasticity)/2;
            

            bodyA.velocity+=projection*e;
            bodyB.velocity-=projection*e;
        }
        else if(registry.hasComponent<CRigidbody>(collision.entityA))
        {
            CRigidbody& body = registry.getComponent<CRigidbody>(collision.entityA);
            vec2 projection = Utils::Project(body.velocity,collision.normal);
            tfA.pos = tfA.pos+collision.mtv;
            body.velocity-=projection*body.elasticity;
        }
        
        else if (registry.hasComponent<CRigidbody>(collision.entityB))
        {
            CRigidbody& body = registry.getComponent<CRigidbody>(collision.entityB);
            vec2 projection = Utils::Project(body.velocity,collision.normal);
            tfB.pos = tfB.pos-collision.mtv;
            body.velocity-=projection*body.elasticity;
            
        }
            
        if(registry.hasComponent<CDamage>(collision.entityA)&&registry.hasComponent<CHealth>(collision.entityB))
        {
            const auto damge = registry.getComponent<CDamage>(collision.entityA);
            Factory::createDamageEvent(registry,collision.entityB,damge.damage);
        }
        if(registry.hasComponent<CDamage>(collision.entityB)&&registry.hasComponent<CHealth>(collision.entityA))
        {
            const auto damge = registry.getComponent<CDamage>(collision.entityB);
            Factory::createDamageEvent(registry,collision.entityA,damge.damage);
        }
    }
    
    registry.clearEntities<CCollisionEvent>();
}



void SPhysics::checkCollisions(Registry& registry)
{
    
    const std::vector<unsigned> boxes = registry.getEntities<CBoxCollider>();
    const std::vector<unsigned> circles = registry.getEntities<CCircleCollider>();
    for (size_t i =0; i< boxes.size();++i)
    {
        for(size_t j = i+1; j<boxes.size(); ++j)
        {
            boxBox(registry,boxes[i],boxes[j]);
        }
        for(size_t k = 0; k<circles.size(); ++k)
        {
            boxCircle(registry,boxes[i],circles[k]);
        }
    }
    for (size_t i =0; i< circles.size();++i)
    {
        for(size_t j = i+1; j<circles.size(); ++j)
        {
            circleCircle(registry,circles[i],circles[j]);
        }
    }
    
}

bool SPhysics::checkCollision(Registry& registry, Entity a, Entity b)
{
    if(registry.hasComponent<CBoxCollider>(a))
    {
        if(registry.hasComponent<CBoxCollider>(b))
        {
            return boxBox(registry,a,b);
        }
        if(registry.hasComponent<CCircleCollider>(b))
        {
            return boxCircle(registry,a,b);
        }
    }
    if(registry.hasComponent<CCircleCollider>(a))
    {
        if(registry.hasComponent<CBoxCollider>(b))
        {
            return boxCircle(registry,b,a);
        }
        if(registry.hasComponent<CCircleCollider>(b))
        {
            return circleCircle(registry,a,b);
        }
    }
    return false;
}


void SPhysics::applyKinematics(Registry& registry, float dt)
{
    for(const auto entityID : registry.getEntities<CRigidbody>())
    {
        CTransform& transform = registry.getComponent<CTransform>(entityID);
        CRigidbody& rigidbody = registry.getComponent<CRigidbody>(entityID);
        
        rigidbody.velocity+= rigidbody.acceleration * dt;
        rigidbody.velocity*=pow((1-rigidbody.drag),dt);
        transform.pos+= rigidbody.velocity * dt;

        rigidbody.acceleration = {0,0};
    }
}

void SPhysics::deleteOffscreen(Registry& registry)
{
    float buffer = 100.0f;
    bool death = false;
    for (auto element : registry.getEntities<CTransform>())
    {
        CTransform& transform = registry.getComponent<CTransform>(element);
        if(transform.pos.x<0-buffer||
            transform.pos.x>1024+buffer||
            transform.pos.y<0-buffer||
            transform.pos.y>768+buffer)
        {
            if(registry.hasComponent<CHealth>(element))
            {
                registry.getComponent<CHealth>(element).bDead = true;
            }
            else
            {
                registry.deleteEntity(element); 
            }
            
        }
    }
}


