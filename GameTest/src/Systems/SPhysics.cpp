#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"

void SPhysics::Update(Scene* scene, float dt)
{
    ApplyKinematics(scene,dt);
    CheckCollisions(scene);
    ResolveCollisions(scene);
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


bool SPhysics::CirclePlane(CCircleCollider circle, CTransform tf1, CPlaneCollider plane, CTransform tf2)
{
    return false;
}

void SPhysics::ResolveCollisions(Scene* scene)
{
    
    for (auto collision : collisions)
    {
        auto tfA = scene->m_register.GetComponent<CTransform>(collision.entityA);
        auto tfB = scene->m_register.GetComponent<CTransform>(collision.entityB);
        if(scene->m_register.HasComponent<CRigidbody>(collision.entityA))
        {
            scene->m_register.GetComponent<CRigidbody>(collision.entityA)->velocity = scene->m_register.GetComponent<CRigidbody>(collision.entityA)->velocity * -1.0f;
        }
        if(scene->m_register.HasComponent<CRigidbody>(collision.entityB))
        {
            scene->m_register.GetComponent<CRigidbody>(collision.entityB)->velocity = scene->m_register.GetComponent<CRigidbody>(collision.entityB)->velocity * -1.0f;
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
    CTransform* transformA = scene->m_register.GetComponent<CTransform>(a);
    CTransform* transformB = scene->m_register.GetComponent<CTransform>(b);

    if(scene->m_register.HasComponent<CBoxCollider>(a))
    {
        auto boxA = scene->m_register.GetComponent<CBoxCollider>(a);
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            auto boxB = scene->m_register.GetComponent<CBoxCollider>(b);
            if(BoxBox(*boxA,*transformA,*boxB,*transformB))
            {
                collisions.push_back({a,b});
                return true;
            };
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            auto circleB = scene->m_register.GetComponent<CCircleCollider>(b);
            if(BoxCircle(*boxA,*transformA,*circleB,*transformB))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
        if(scene->m_register.HasComponent<CPlaneCollider>(b))
        {
            auto plane = scene->m_register.GetComponent<CPlaneCollider>(b);
            if(BoxPlane(*boxA,*transformA,*plane,*transformB))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
    }
    if(scene->m_register.HasComponent<CCircleCollider>(a))
    {
        auto circleA = scene->m_register.GetComponent<CCircleCollider>(a);
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            auto boxB = scene->m_register.GetComponent<CBoxCollider>(b);
            if(BoxCircle(*boxB, *transformB, *circleA, *transformA))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            auto circleB = scene->m_register.GetComponent<CCircleCollider>(b);
            if(CircleCircle(*circleA, *transformA, *circleB, *transformB))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
        if(scene->m_register.HasComponent<CPlaneCollider>(b))
        {
            auto plane = scene->m_register.GetComponent<CPlaneCollider>(b);
            if(CirclePlane(*circleA,*transformA,*plane,*transformB))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
    }
    if(scene->m_register.HasComponent<CPlaneCollider>(a))
    {
        auto plane = scene->m_register.GetComponent<CPlaneCollider>(a);
        if(scene->m_register.HasComponent<CBoxCollider>(b))
        {
            auto box = scene->m_register.GetComponent<CBoxCollider>(b);
            if(BoxPlane(*box,*transformB,*plane,*transformA))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
        if(scene->m_register.HasComponent<CCircleCollider>(b))
        {
            auto circle = scene->m_register.GetComponent<CCircleCollider>(b);
            if(CirclePlane(*circle,*transformB,*plane,*transformA))
            {
                collisions.push_back({a,b});
                return true;
            }
        }
        
    }
    return false;
}

void SPhysics::AddImpulse(vec2 direction, CRigidbody body)
{
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


