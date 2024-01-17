#include "stdafx.h"
#include "ECSTestScene.h"
#include "../Components/Components.h"
#include "../Systems/SButton.h"
#include "../Systems/SDelete.h"
#include "../Systems/SEnemy.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SPlayer.h"
#include "../Systems/SProjectile.h"
#include "../Systems/SRender.h"

void ECSTestScene::Init()
{
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SButton>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SDelete>();
    reg.CreateSystem<SProjectile>();

    
    
    reg.CreateComponentArray<CCircleCollider>();
    reg.CreateComponentArray<CCollisionEvent>();
    reg.CreateComponentArray<CImpulseEvent>();
    reg.CreateComponentArray<CButton>();
    reg.CreateComponentArray<CPlayer>();
    reg.CreateComponentArray<CCamera>();
    reg.CreateComponentArray<CCollider>();
    reg.CreateComponentArray<CBoxCollider>();
    reg.CreateComponentArray<CRender>();
    reg.CreateComponentArray<CTransform>();
    reg.CreateComponentArray<CRigidbody>();
    reg.CreateComponentArray<CHealth>();
    reg.CreateComponentArray<CDeleteMe>();
    reg.CreateComponentArray<CProjectile>();

    
    //auto camera = reg.CreateEntity();
    //reg.AddComponent(camera, CCamera());
    //reg.AddComponent(camera,CTransform({0,0}));
    //reg.GetSystem<SRender>()->Init(*this);
    for (int i = 0; i < MAX_IDS; ++i)
    {
        reg.CreateEntity();
    }
}

void ECSTestScene::Update(float dt)
{
    dt/=1000.0f;
    if(count<MAX_IDS-1)
    {
        count++;
        /*reg.AddComponent(ID,CCircleCollider(50));
        reg.AddComponent(ID, CButton());
        reg.AddComponent(ID,CPlayer());
        reg.AddComponent(ID,CCollider());
        reg.AddComponent(ID,CRender());
        reg.AddComponent(ID,CHealth());
        reg.AddComponent(ID,CProjectile());*/
        reg.AddComponent(count,CTransform());
        reg.AddComponent(count,CRigidbody());
        reg.AddComponent(count,CHealth());
        reg.RemoveComponent<CTransform>(count);
        reg.AddComponent(count,CTransform());
    }
    else
    {
        count = 0;
        reg.ClearComponents<CTransform>();
        reg.ClearComponents<CRigidbody>();
        reg.ClearComponents<CHealth>();
    }
    reg.GetSystem<SRender>()->Update(*this);
    reg.GetSystem<SPlayer>()->Update(*this,dt);
    //reg.GetSystem<SPhysics>()->Update(this,dt);
    reg.GetSystem<SProjectile>()->Update(*this,dt);
    reg.GetSystem<SDelete>()->Update(*this);
}

void ECSTestScene::Shutdown()
{
    
}
