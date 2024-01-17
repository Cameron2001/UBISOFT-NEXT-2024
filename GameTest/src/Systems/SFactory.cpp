#include "stdafx.h"
#include "SFactory.h"

Entity SFactory::CreatePlayer(Scene& scene, vec2 pos, vec2 bounds, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    scene.reg.AddComponent(id, CPlayer());
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

Entity SFactory::CreateEnemy(Scene& scene, vec2 pos, vec2 bounds, Entity id)
{
    if(id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    scene.reg.AddComponent(id, CEnemy());
    scene.reg.AddComponent(id, CHealth(200));
    return id;
}

Entity SFactory::CreateBox(Scene& scene, vec2 pos, vec2 bounds, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRigidbody());
    scene.reg.AddComponent(id, CRender());
    scene.reg.AddComponent(id, CCollider());
    scene.reg.AddComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity SFactory::CreateCircle(Scene& scene, vec2 pos, float radius, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRigidbody());
    scene.reg.AddComponent(id, CRender());
    scene.reg.AddComponent(id, CCollider());
    scene.reg.AddComponent(id,CCircleCollider(radius));
    return id;
}

Entity SFactory::CreateCamera(Scene& scene, vec2 pos, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CCamera());
    scene.reg.AddComponent(id, CTransform(pos));
    return id;
}

Entity SFactory::CreateProjectile(Scene& scene, vec2 pos, float radius, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    CreateCircle(scene,pos,radius,id);
    scene.reg.AddComponent(id,CProjectile());
    return id;
    
}

Entity SFactory::CreateDamageEvent(Scene& scene, Entity target, float damage, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CDamageEvent(target,damage));
    return id;
}

Entity SFactory::CreateImpulseEvent(Scene& scene, Entity target, vec2 dir, float force, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CImpulseEvent(target,dir,force));
    return id;
}

Entity SFactory::CreateCollisionEvent(Scene& scene, Entity entityA, Entity entityB, vec2 mtv, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CCollisionEvent(entityA,entityB,mtv));
    return id;
}


