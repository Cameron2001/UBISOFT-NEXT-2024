#include "stdafx.h"
#include "SPlayer.h"

#include "SFactory.h"
#include "../../App/app.h"
#include "../Util/Utils.h"


void SPlayer::Init(Scene& scene)
{
}

void SPlayer::Update(Scene& scene, float dt)
{
    for(auto entityID : scene.reg.GetEntities<CPlayer>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        CPlayer* player = scene.reg.GetComponent<CPlayer>(entityID);
        CRigidbody* rigidbody = scene.reg.GetComponent<CRigidbody>(entityID);
        bool up = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false) || App::IsKeyPressed('W');
        bool down = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false) || App::IsKeyPressed('S');
        bool left = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false) || App::IsKeyPressed('A');
        bool right = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false) || App::IsKeyPressed('D');
        bool shoot  = App::IsKeyPressed(VK_SPACE)|| App::IsKeyPressed(VK_LBUTTON);
        if (up)
        {
            rigidbody->acceleration  = rigidbody->acceleration+ vec2{0,player->moveSpeed};
        }
        if (down)
        {
            rigidbody->acceleration = rigidbody->acceleration - vec2{0,player->moveSpeed};
        }
        if (right)
        {
            rigidbody->acceleration = rigidbody->acceleration + vec2{player->moveSpeed,0};
        }
        if (left)
        {
            rigidbody->acceleration = rigidbody->acceleration - vec2{player->moveSpeed,0};
        }
        if(shoot && player->state==CPlayer::States::IDLE&&player->ammo>0)
        {
            player->state=CPlayer::States::SHOOTING;
            player->timer = 0;
        }
        if(player->state==CPlayer::States::SHOOTING)
        {
            player->timer+=dt;
            if(shoot == false)
            {
                scene.reg.GetSystem<SFactory>()->CreateProjectile(scene,transform->pos,50*player->timer,50000*player->timer,player->rot,100*player->timer,50*player->timer);
                player->state=CPlayer::States::RELOADING;
                player->timer = 0;
            }
        }
        if(player->state==CPlayer::States::RELOADING)
        {
            player->timer +=dt;
            if(player->timer>player->shootCooldown)
            {
                player->state = CPlayer::States::IDLE;
            }
        }
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        player->rot = atan2(mousePos.y-transform->pos.y,mousePos.x-transform->pos.x);
    }
}



