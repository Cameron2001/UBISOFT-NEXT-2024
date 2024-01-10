#include "stdafx.h"
#include "PlayScene.h"

#include "../Components/Components.h"
#include "../Systems/SEnemy.h"
#include "../Systems/SFactory.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SPlayer.h"
#include "../Systems/SRender.h"

PlayScene::~PlayScene()
=default;

void PlayScene::Init()
{
    reg.CreateSystem<SPlayer>();
    reg.CreateSystem<SPhysics>();
    reg.CreateSystem<SRender>();
    reg.CreateSystem<SEnemy>();
    reg.CreateSystem<SFactory>();
    
    reg.GetSystem<SFactory>()->CreateCamera(this,{0,0});
    reg.GetSystem<SFactory>()->CreatePlayer(this,{200,300},{50,25});
    reg.GetSystem<SFactory>()->CreateBox(this,{500,400},{25,25});
    reg.GetSystem<SFactory>()->CreateCircle(this,{100,100},60);
    
    reg.GetSystem<SRender>()->Init(this);
    reg.GetSystem<SPlayer>()->Init(this);
   
}

void PlayScene::Update(float dt)
{
    dt/=1000.0f;
    reg.GetSystem<SPlayer>()->Update(this,dt);
    reg.GetSystem<SPhysics>()->Update(this,dt);
}

void PlayScene::Render()
{
    reg.GetSystem<SRender>()->Update(this);
}

void PlayScene::Shutdown()
{
    
}
