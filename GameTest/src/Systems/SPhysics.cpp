#include "stdafx.h"
#include "SPhysics.h"

#include "../Util/Utils.h"

void SPhysics::Update(Scene* scene, float dt)
{
    ApplyKinematics(scene,dt);
    CheckCollisions(scene);
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
{return false;
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
        
    }
}



void SPhysics::CheckCollisions(Scene* scene)
{
    auto boxes = scene->m_register.GetEntities<CBoxCollider>();
    for (size_t i =0; i< boxes.size();i++)
    {
        CTransform* transformI = scene->m_register.GetComponent<CTransform>(boxes[i]);
        CBoxCollider* boxI = scene->m_register.GetComponent<CBoxCollider>(boxes[i]);
        for(size_t j = i+1; j<boxes.size(); j++)
        {
            CTransform* transformJ = scene->m_register.GetComponent<CTransform>(boxes[j]);
            CBoxCollider* boxJ = scene->m_register.GetComponent<CBoxCollider>(boxes[j]);
            if(BoxBox(*boxI, *transformI, *boxJ, *transformJ))
            {
                collisions.push_back({boxes[i],boxes[j]});
            }
        }
    } 
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


