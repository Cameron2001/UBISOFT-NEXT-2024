#include "stdafx.h"
#include "SPlayer.h"
#include "../../App/app.h"
void SPlayer::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CPlayer>())
    {
        CTransform* transform = scene->m_register.GetComponent<CTransform>(entityID);
        CPlayer* player = scene->m_register.GetComponent<CPlayer>(entityID);
        CRigidbody* rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);

        float speed = 10;
        bool up = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false) || App::IsKeyPressed('W');
        bool down = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false) || App::IsKeyPressed('S');
        bool left = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false) || App::IsKeyPressed('A');
        bool right = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false) || App::IsKeyPressed('D');
        

        if (up)
        {
            transform->pos.y += speed;
        }
        if (down)
        {
            transform->pos.y -= speed;
        }
        if (right)
        {
            transform->pos.x += speed;
        }
        if (left)
        {
            transform->pos.x -= speed;
        }
        
    }
}


