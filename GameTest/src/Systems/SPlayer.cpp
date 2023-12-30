#include "stdafx.h"
#include "SPlayer.h"
#include "../../App/app.h"

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
        bool add  = App::IsKeyPressed('I');;
        bool del = App::IsKeyPressed('O'); ;
        

        if (up)
        {
            //transform->pos.y += player->moveSpeed;
            rigidbody->acceleration  = rigidbody->acceleration+ vec2{0,player->moveSpeed};
        }
        if (down)
        {
            //transform->pos.y -= player->moveSpeed;
            rigidbody->acceleration = rigidbody->acceleration - vec2{0,player->moveSpeed};
        }
        if (right)
        {
            //transform->pos.x += player->moveSpeed;
            rigidbody->acceleration = rigidbody->acceleration + vec2{player->moveSpeed,0};
        }
        if (left)
        {
            //transform->pos.x -= player->moveSpeed;
            rigidbody->acceleration = rigidbody->acceleration - vec2{player->moveSpeed,0};
        }
        if (add)
        {
        }
        if(del)
        {
            
        }
        
    }
}


