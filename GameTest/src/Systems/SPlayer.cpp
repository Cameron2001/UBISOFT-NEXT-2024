#include "stdafx.h"
#include "SPlayer.h"
#include "../../App/app.h"
#include "../Components/CImpulseEvent.h"
#include "../Util/Utils.h"


void SPlayer::Init(Scene& scene)
{
    m_camera = scene.reg.GetEntities<CCamera>()[0];
}

void SPlayer::Update(Scene& scene, float dt)
{
    for(auto entityID : scene.reg.GetEntities<CPlayer>())
    {
        CTransform& transform = scene.reg.GetComponent<CTransform>(entityID);
        CPlayer& player = scene.reg.GetComponent<CPlayer>(entityID);
        bool up = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false) || App::IsKeyPressed('W');
        bool down = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false) || App::IsKeyPressed('S');
        bool left = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false) || App::IsKeyPressed('A');
        bool right = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false) || App::IsKeyPressed('D');
        bool shoot  = App::IsKeyPressed(VK_SPACE);
        

        if (up)
        {
            //transform.pos.y += player.moveSpeed;
            auto impulse = scene.reg.CreateEntity();
            scene.reg.AddComponent(impulse, CImpulseEvent(entityID,{0,1},player.moveSpeed));
            //rigidbody.acceleration  = rigidbody.acceleration+ vec2{0,player.moveSpeed};
        }
        if (down)
        {
            //transform.pos.y -= player.moveSpeed;
            auto impulse = scene.reg.CreateEntity();
            scene.reg.AddComponent(impulse, CImpulseEvent(entityID,{0,-1},player.moveSpeed));
            //rigidbody.acceleration = rigidbody.acceleration - vec2{0,player.moveSpeed};
        }
        if (right)
        {
            //transform.pos.x += player.moveSpeed;
            auto impulse = scene.reg.CreateEntity();
            scene.reg.AddComponent(impulse, CImpulseEvent(entityID,{1,0},player.moveSpeed));
            //rigidbody.acceleration = rigidbody.acceleration + vec2{player.moveSpeed,0};
        }
        if (left)
        {
            //transform.pos.x -= player.moveSpeed;
            auto impulse = scene.reg.CreateEntity();
            scene.reg.AddComponent(impulse, CImpulseEvent(entityID,{-1,0},player.moveSpeed));
            //rigidbody.acceleration = rigidbody.acceleration - vec2{player.moveSpeed,0};
        }
        if(shoot)
        {
            
            auto bullet = scene.reg.CreateEntity();
            scene.reg.AddComponent(bullet,CRigidbody());
            scene.reg.AddComponent(bullet,CTransform({transform.pos.x,transform.pos.y}));
            scene.reg.AddComponent(bullet, CCircleCollider(50));
            scene.reg.AddComponent(bullet, CRender());
            scene.reg.AddComponent(bullet, CCollider());
            scene.reg.GetComponent<CRigidbody>(bullet).acceleration.x+=500;
            scene.reg.GetComponent<CRigidbody>(bullet).acceleration.y+=500;
        }
        
        //scene->m_register.GetComponent<CTransform>(m_camera)->pos={transform->pos.x-APP_VIRTUAL_WIDTH/2,transform->pos.y-APP_VIRTUAL_HEIGHT/2};
        //scene->reg.GetComponent<CTransform>(m_camera)->pos= Utils::Lerp(scene->reg.GetComponent<CTransform>(m_camera)->pos,{transform->pos.x-APP_VIRTUAL_WIDTH/2,transform->pos.y-APP_VIRTUAL_HEIGHT/2},0.1);
        
    }
}



