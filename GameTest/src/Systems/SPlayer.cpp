#include "stdafx.h"
#include "SPlayer.h"

#include "../../App/app.h"
#include "../Core/Factory.h"
#include "../Util/Utils.h"


void SPlayer::Update(Registry& Registry, float dt)
{
    for(const auto entityID : Registry.GetEntities<CPlayer>())
    {
        const CTransform* transform = Registry.GetComponent<CTransform>(entityID);
        CPlayer* player = Registry.GetComponent<CPlayer>(entityID);
        CRigidbody* rigidbody = Registry.GetComponent<CRigidbody>(entityID);
        CTimer* timer = Registry.GetComponent<CTimer>(entityID);
        CArm* arm = Registry.GetComponent<CArm>(entityID);
        bool up = App::IsKeyPressed('W');
        bool down = App::IsKeyPressed('S');
        bool left = App::IsKeyPressed('A');
        bool right = App::IsKeyPressed('D');
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
        if(shoot && player->state==CPlayer::States::IDLE)
        {
            player->state=CPlayer::States::SHOOTING;
            timer->timer = 0;
        }
        if(player->state==CPlayer::States::SHOOTING)
        {
            if(shoot == false)
            {
                float multi = Utils::Clamp(timer->timer,0.5f,2.5f);
                Factory::CreateProjectile(Registry,transform->pos,24*multi,50000*multi,arm->rotation,50*multi,50*multi);
                player->state=CPlayer::States::RELOADING;
                timer->timer = 0;
            }
        }
        if(player->state==CPlayer::States::RELOADING)
        {
            if(timer->timer>player->shootCooldown)
            {
                player->state = CPlayer::States::IDLE;
            }
        }
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        arm->rotation= atan2(mousePos.y-transform->pos.y,mousePos.x-transform->pos.x);
        CLabel* label = Registry.GetComponent<CLabel>(entityID);
        label->labelText = "Health: " + std::to_string(Registry.GetComponent<CHealth>(entityID)->hp);
    }
}



