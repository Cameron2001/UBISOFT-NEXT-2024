#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"

void SPhysics::Update(Scene* scene, float dt)
{
    ApplyKinematics(scene,dt);
    CheckCollisions(scene);
    ResolveCollisions(scene);
}

bool SPhysics::BoxBox(Scene* scene, Entity aID, Entity bID)
{
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
    collisions.push_back({aID,bID});
    return true;
}

bool SPhysics::BoxBox(CBoxCollider box1, CTransform tf1, CBoxCollider box2, CTransform tf2)
{
    float xMin1 = tf1.pos.x - box1.extents.x;
    float xMax1 = tf1.pos.x + box1.extents.x;
    float yMin1 = tf1.pos.y - box1.extents.y;
    float yMax1 = tf1.pos.y + box1.extents.y;

    float xMin2 = tf2.pos.x - box2.extents.x;
    float xMax2 = tf2.pos.x + box2.extents.x;
    float yMin2 = tf2.pos.y - box2.extents.y;
    float yMax2 = tf2.pos.y + box2.extents.y;
    
    if(xMax1 < xMin2 || xMin1 > xMax2) return false;
    if(yMax1 < yMin2 || yMin1 > yMax2) return false;
    
    return true;
}

bool SPhysics::BoxCircle(CBoxCollider box, CTransform tf1, CCircleCollider circle, CTransform tf2)
{
    float x = Utils::Clamp(tf2.pos.x,tf1.pos.x-box.extents.x,tf1.pos.x+box.extents.x);
    float y = Utils::Clamp(tf2.pos.y,tf1.pos.y-box.extents.y,tf1.pos.y+box.extents.y);
    if(Utils::Distance({x,y},tf2.pos)<circle.radius)
    {
        return true;
    }
    return false;
    
}

bool SPhysics::BoxCircle(Scene* scene, Entity boxID, Entity circleID)
{
    auto tf1 = scene->m_register.GetComponent<CTransform>(boxID);
    auto tf2 = scene->m_register.GetComponent<CTransform>(circleID);
    auto box = scene->m_register.GetComponent<CBoxCollider>(boxID);
    auto circle = scene->m_register.GetComponent<CCircleCollider>(circleID);
    float x = Utils::Clamp(tf2->pos.x,tf1->pos.x-box->extents.x,tf1->pos.x+box->extents.x);
    float y = Utils::Clamp(tf2->pos.y,tf1->pos.y-box->extents.y,tf1->pos.y+box->extents.y);
    if(Utils::Distance({x,y},tf2->pos)<circle->radius)
    {
        collisions.push_back({boxID,circleID});
        return true;
    }
    return false;
    
}


bool SPhysics::BoxPlane(CBoxCollider box, CTransform tf1, CPlaneCollider plane, CTransform tf2)
{
    return false;
}

bool SPhysics::BoxPlane(Scene* scene, Entity boxID, Entity planeID)
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
        collisions.push_back({aID,bID});
        return true;
    }
    return false;
}


bool SPhysics::CirclePlane(CCircleCollider circle, CTransform tf1, CPlaneCollider plane, CTransform tf2)
{
    return false;
}

bool SPhysics::CirclePlane(Scene* scene, Entity circleID, Entity planeID)
{
    return false;
}


void SPhysics::ResolveCollisions(Scene* scene)
{
    
    for (auto collision : collisions)
    {
        auto tfA = scene->m_register.GetComponent<CTransform>(collision.entityA);
        auto tfB = scene->m_register.GetComponent<CTransform>(collision.entityB);
        auto rbA = scene->m_register.GetComponent<CRigidbody>(collision.entityA);
        auto rbB = scene->m_register.GetComponent<CRigidbody>(collision.entityB);
        if(scene->m_register.HasComponent<CRigidbody>(collision.entityA))
        {
            rbA->velocity = rbA->velocity*-1.0f;
        }
        if(scene->m_register.HasComponent<CRigidbody>(collision.entityB))
        {
            rbB->velocity = rbB->velocity*-1.0f;
        }
        tfA->pos = tfA->pos+collision.mtv;
    }
    collisions.clear();
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
        if(scene->m_register.HasComponent<CPlaneCollider>(b))
        {
            return BoxPlane(scene,a,b);
        }
    }
    if(scene->m_register.HasComponent<CCircleCollider>(a))
    {
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            return BoxCircle(scene,a,b);
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            return CircleCircle(scene,a,b);
        }
        if(scene->m_register.HasComponent<CPlaneCollider>(b))
        {
            return CirclePlane(scene,a,b);
        }
    }
    if(scene->m_register.HasComponent<CPlaneCollider>(a))
    {
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            return BoxPlane(scene, b, a);
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            return CirclePlane(scene,b,a);
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


