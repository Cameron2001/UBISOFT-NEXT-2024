#include "stdafx.h"
#include "SFactory.h"

#include "../Util/Utils.h"

Entity SFactory::CreatePlayer(Scene& scene, vec2 pos, float radius, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    //CreateBox(scene,pos,{25,25},id);
    CreateCircle(scene,pos,radius,id);
    scene.reg.AddComponent(id, CPlayer(10,1000));
    scene.reg.AddComponent(id,CRigidbody());
    scene.reg.AddComponent(id,CHealth(100));
    return id;
}

Entity SFactory::CreateButton(Scene& scene, vec2 pos, vec2 bounds,Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    return id;
}

Entity SFactory::CreateEnemy(Scene& scene, vec2 pos, vec2 bounds, float hp, Entity id)
{
    if(id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    scene.reg.AddComponent(id, CEnemy());
    scene.reg.AddComponent(id, CHealth(hp));
    scene.reg.AddComponent(id, CRigidbody());
    return id;
}

Entity SFactory::CreateBox(Scene& scene, vec2 pos, vec2 bounds,  Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRender());
    scene.reg.AddComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity SFactory::CreateCircle(Scene& scene, vec2 pos, float radius, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRender());
    scene.reg.AddComponent(id,CCircleCollider(radius));
    return id;
}


Entity SFactory::CreateProjectile(Scene& scene, vec2 pos, float radius, float force, float angle, float health, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    CreateCircle(scene,pos+(dir*(radius+50.0f)),radius,id);
    scene.reg.AddComponent(id, CHealth(health));
    scene.reg.AddComponent(id,CRigidbody(0));
    scene.reg.GetComponent<CRigidbody>(id)->acceleration+=dir*force;
    return id;
    
}

Entity SFactory::CreateDamageEvent(Scene& scene, Entity target, float damage, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CDamageEvent(target,damage));
    return id;
}



Entity SFactory::CreateCollisionEvent(Scene& scene, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CCollisionEvent(entityA,entityB,mtv, normal));
    return id;
}


