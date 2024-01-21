#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"
#include "../Components/Components.h"
#include "../Core/DeathScene.h"
#include "../Core/Factory.h"
#include "../Core/SceneManager.h"

void SPhysics::update(Registry& Registry, float dt)
{
    deleteOffscreen(Registry);
    checkCollisions(Registry);
    resolveCollisions(Registry);
    applyKinematics(Registry,dt);
}

bool SPhysics::boxBox(Registry& Registry, Entity aID, Entity bID)
{
    //clean this up. all determine which side of the box was collided with
    if(aID == bID) return false;
    if(!Registry.hasComponent<CRigidbody>(aID) && !Registry.hasComponent<CRigidbody>(bID)) return false;
    
    CBoxCollider& box1 = Registry.getComponent<CBoxCollider>(aID);
    CBoxCollider& box2 = Registry.getComponent<CBoxCollider>(bID);
    vec2 pos1 = Registry.getComponent<CTransform>(aID).pos+box1.offset;
    vec2 pos2 = Registry.getComponent<CTransform>(bID).pos+box2.offset;
    vec2 diff = {pos2-pos1};
    
    auto x = (box1.extents.x+box2.extents.x) - abs(diff.x);
    auto y = (box1.extents.y+box2.extents.y) - abs(diff.y);
    if(x<=0 || y<=0)    return false;
    if (x<y)
    {
        auto sx = Utils::Sign(diff.x);
        vec2 normal = {-sx,0};
        vec2 mtv = {-x * sx,0};
        Factory::createCollisionEvent(Registry,aID,bID,mtv,normal);
    }
    else if (x>y)
    {
        auto sy = Utils::Sign(diff.y);
        vec2 normal = {0,-sy};
        vec2 mtv = {0,y * -sy};
        Factory::createCollisionEvent(Registry,aID,bID,mtv,normal);
    }
    
    
    
    
    return true;
}



bool SPhysics::boxCircle(Registry& Registry, Entity boxID, Entity circleID)
{
    if(boxID == circleID) return false;
    if(!Registry.hasComponent<CRigidbody>(boxID) && !Registry.hasComponent<CRigidbody>(circleID)) return false;
    
    const CBoxCollider& box = Registry.getComponent<CBoxCollider>(boxID);
    const CCircleCollider& circle = Registry.getComponent<CCircleCollider>(circleID);
    const vec2 pos1 = Registry.getComponent<CTransform>(boxID).pos+box.offset;
    const vec2 pos2 = Registry.getComponent<CTransform>(circleID).pos+circle.offset;
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
        Factory::createCollisionEvent(Registry,boxID,circleID,mtv,normal);
        return true;
    }
    return false;
    
}


bool SPhysics::circleCircle(Registry& Registry, Entity aID, Entity bID)
{
    if(aID == bID) return false;
    if(!Registry.hasComponent<CRigidbody>(aID) && !Registry.hasComponent<CRigidbody>(bID)) return false;
    
    const CCircleCollider& circle1 = Registry.getComponent<CCircleCollider>(aID);
    const CCircleCollider& circle2 = Registry.getComponent<CCircleCollider>(bID);
    const vec2 pos1 = Registry.getComponent<CTransform>(aID).pos+circle1.offset;
    const vec2 pos2 =Registry.getComponent<CTransform>(bID).pos+circle2.offset;
    const float distance = Utils::Distance(pos1,pos2);
    const float radiiSum = circle1.radius + circle2.radius;
    if( distance <= radiiSum)
    {
        const float minDist = distance-radiiSum;
        const vec2 diff = pos2-pos1;
        //diff = {abs(diff.x),abs(diff.y)};
        const vec2 normal = Utils::Normalize(diff);
        const vec2 mtv = Utils::Normalize(diff)*minDist;
        Factory::createCollisionEvent(Registry,aID,bID,mtv,normal);
        return true;
    }
    return false;
}


void SPhysics::resolveCollisions(Registry& Registry)
{
    for (auto current : Registry.getEntities<CCollisionEvent>())
    {
        const CCollisionEvent& collision = Registry.getComponent<CCollisionEvent>(current);
        CTransform& tfA = Registry.getComponent<CTransform>(collision.entityA);
        CTransform& tfB = Registry.getComponent<CTransform>(collision.entityB);
        if(Registry.hasComponent<CRigidbody>(collision.entityA)&&Registry.hasComponent<CRigidbody>(collision.entityB))
        {
            tfA.pos = tfA.pos+(collision.mtv/2);
            tfB.pos = tfB.pos-(collision.mtv/2);
            
            CRigidbody& bodyA = Registry.getComponent<CRigidbody>(collision.entityA);
            CRigidbody& bodyB = Registry.getComponent<CRigidbody>(collision.entityB);
            vec2 veloAlongNormal = bodyB.velocity-bodyA.velocity;
            vec2 projection = Utils::Project(veloAlongNormal,collision.normal);
            float e = (bodyA.elasticity+bodyB.elasticity)/2;
            

            bodyA.velocity+=projection*e;
            bodyB.velocity-=projection*e;
        }
        else if(Registry.hasComponent<CRigidbody>(collision.entityA))
        {
            CRigidbody& body = Registry.getComponent<CRigidbody>(collision.entityA);
            vec2 projection = Utils::Project(body.velocity,collision.normal);
            tfA.pos = tfA.pos+collision.mtv;
            body.velocity-=projection*body.elasticity;
        }
        
        else if (Registry.hasComponent<CRigidbody>(collision.entityB))
        {
            CRigidbody& body = Registry.getComponent<CRigidbody>(collision.entityB);
            vec2 projection = Utils::Project(body.velocity,collision.normal);
            tfB.pos = tfB.pos-collision.mtv;
            body.velocity-=projection*body.elasticity;
            
        }
            
        if(Registry.hasComponent<CDamage>(collision.entityA)&&Registry.hasComponent<CHealth>(collision.entityB))
        {
            const auto damge = Registry.getComponent<CDamage>(collision.entityA);
            Factory::createDamageEvent(Registry,collision.entityB,damge.damage);
        }
        if(Registry.hasComponent<CDamage>(collision.entityB)&&Registry.hasComponent<CHealth>(collision.entityA))
        {
            const auto damge = Registry.getComponent<CDamage>(collision.entityB);
            Factory::createDamageEvent(Registry,collision.entityA,damge.damage);
        }
    }
    
    Registry.clearEntities<CCollisionEvent>();
}



void SPhysics::checkCollisions(Registry& Registry)
{
    
    const std::vector<unsigned> boxes = Registry.getEntities<CBoxCollider>();
    const std::vector<unsigned> circles = Registry.getEntities<CCircleCollider>();
    for (size_t i =0; i< boxes.size();++i)
    {
        for(size_t j = i+1; j<boxes.size(); ++j)
        {
            boxBox(Registry,boxes[i],boxes[j]);
        }
        for(size_t k = 0; k<circles.size(); ++k)
        {
            boxCircle(Registry,boxes[i],circles[k]);
        }
    }
    for (size_t i =0; i< circles.size();++i)
    {
        for(size_t j = i+1; j<circles.size(); ++j)
        {
            circleCircle(Registry,circles[i],circles[j]);
        }
    }
    
}

bool SPhysics::checkCollision(Registry& Registry, Entity a, Entity b)
{
    if(Registry.hasComponent<CBoxCollider>(a))
    {
        if(Registry.hasComponent<CBoxCollider>(b))
        {
            return boxBox(Registry,a,b);
        }
        if(Registry.hasComponent<CCircleCollider>(b))
        {
            return boxCircle(Registry,a,b);
        }
    }
    if(Registry.hasComponent<CCircleCollider>(a))
    {
        if(Registry.hasComponent<CBoxCollider>(b))
        {
            return boxCircle(Registry,b,a);
        }
        if(Registry.hasComponent<CCircleCollider>(b))
        {
            return circleCircle(Registry,a,b);
        }
    }
    return false;
}


void SPhysics::applyKinematics(Registry& Registry, float dt)
{
    for(const auto entityID : Registry.getEntities<CRigidbody>())
    {
        CTransform& transform = Registry.getComponent<CTransform>(entityID);
        CRigidbody& rigidbody = Registry.getComponent<CRigidbody>(entityID);
        
        rigidbody.velocity+= rigidbody.acceleration * dt;
        rigidbody.velocity*=pow((1-rigidbody.drag),dt);
        transform.pos+= rigidbody.velocity * dt;

        rigidbody.acceleration = {0,0};
    }
}

void SPhysics::deleteOffscreen(Registry& Registry)
{
    float buffer = 100.0f;
    bool death = false;
    for (auto element : Registry.getEntities<CTransform>())
    {
        CTransform& transform = Registry.getComponent<CTransform>(element);
        if(transform.pos.x<0-buffer||
            transform.pos.x>1024+buffer||
            transform.pos.y<0-buffer||
            transform.pos.y>768+buffer)
        {
            if(Registry.hasComponent<CHealth>(element))
            {
                Registry.getComponent<CHealth>(element).isDead = true;
            }
            else
            {
                Registry.deleteEntity(element); 
            }
            
        }
    }
}


