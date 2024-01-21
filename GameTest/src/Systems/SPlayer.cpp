#include "stdafx.h"
#include "SPlayer.h"

#include "SFactory.h"
#include "../../App/app.h"
#include "../Util/Utils.h"


void SPlayer::Update(Scene& scene, float dt)
{
    for(auto entityID : scene.reg.GetEntities<CPlayer,CTransform,CRigidbody,CTimer>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        CPlayer* player = scene.reg.GetComponent<CPlayer>(entityID);
        CRigidbody* rigidbody = scene.reg.GetComponent<CRigidbody>(entityID);
        CTimer* timer = scene.reg.GetComponent<CTimer>(entityID);
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
        if(shoot && player->state==CPlayer::States::IDLE&&player->ammo>0)
        {
            player->state=CPlayer::States::SHOOTING;
            timer->timer = 0;
        }
        if(player->state==CPlayer::States::SHOOTING)
        {
            if(shoot == false)
            {
                float multi = Utils::Clamp(timer->timer,0.5f,2.0f);
                scene.reg.GetSystem<SFactory>()->CreateProjectile(scene,transform->pos,30*multi,35000*multi,player->rot,100*multi,50*multi);
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
        player->rot = atan2(mousePos.y-transform->pos.y,mousePos.x-transform->pos.x);
    }
}



