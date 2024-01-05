#include "stdafx.h"
#include "SPlayer.h"
#include "../../App/app.h"
#include "../Components/CImpulseEvent.h"

void SPlayer::Init()
{
}

void SPlayer::Update(Scene* scene, float dt)
{
    for(auto entityID : scene->m_register.GetEntities<CPlayer>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CPlayer* player = scene->m_register.GetComponent<CPlayer>(entityID);
        CRigidbody* rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);
        bool up = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false) || App::IsKeyPressed('W');
        bool down = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false) || App::IsKeyPressed('S');
        bool left = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false) || App::IsKeyPressed('A');
        bool right = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false) || App::IsKeyPressed('D');
        bool shoot  = App::IsKeyPressed(VK_SPACE);
        

        if (up)
        {
            //transform->pos.y += player->moveSpeed;
            auto impulse = scene->m_register.CreateEntity();
            scene->m_register.AddComponent(impulse, CImpulseEvent(entityID,{0,1},player->moveSpeed));
            //rigidbody->acceleration  = rigidbody->acceleration+ vec2{0,player->moveSpeed};
        }
        if (down)
        {
            //transform->pos.y -= player->moveSpeed;
            auto impulse = scene->m_register.CreateEntity();
            scene->m_register.AddComponent(impulse, CImpulseEvent(entityID,{0,-1},player->moveSpeed));
            //rigidbody->acceleration = rigidbody->acceleration - vec2{0,player->moveSpeed};
        }
        if (right)
        {
            //transform->pos.x += player->moveSpeed;
            auto impulse = scene->m_register.CreateEntity();
            scene->m_register.AddComponent(impulse, CImpulseEvent(entityID,{1,0},player->moveSpeed));
            //rigidbody->acceleration = rigidbody->acceleration + vec2{player->moveSpeed,0};
        }
        if (left)
        {
            //transform->pos.x -= player->moveSpeed;
            auto impulse = scene->m_register.CreateEntity();
            scene->m_register.AddComponent(impulse, CImpulseEvent(entityID,{-1,0},player->moveSpeed));
            //rigidbody->acceleration = rigidbody->acceleration - vec2{player->moveSpeed,0};
        }
        if(shoot)
        {
            
            auto bullet = scene->m_register.CreateEntity();
            scene->m_register.AddComponent(bullet,CRigidbody());
            scene->m_register.AddComponent(bullet,CTransform({transform->pos.x,transform->pos.y}));
            scene->m_register.AddComponent(bullet, CCircleCollider(50));
            scene->m_register.AddComponent(bullet, CRender());
            scene->m_register.AddComponent(bullet, CCollider());
            scene->m_register.GetComponent<CRigidbody>(bullet)->acceleration.x+=500;
            scene->m_register.GetComponent<CRigidbody>(bullet)->acceleration.y+=500;
        }
        
    }
}



