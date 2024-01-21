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
        CArm* arm = Registry.GetComponent<CArm>(entityID);
        CShield* shield = Registry.GetComponent<CShield>(entityID);
        bool up = App::IsKeyPressed('W');
        bool down = App::IsKeyPressed('S');
        bool left = App::IsKeyPressed('A');
        bool right = App::IsKeyPressed('D');
        arm->shoot = App::IsKeyPressed(VK_LBUTTON);
        shield->isEnabled =  App::IsKeyPressed(VK_SPACE);
        if (up) rigidbody->acceleration  = rigidbody->acceleration+ vec2{0,player->moveSpeed};
        if (down)rigidbody->acceleration = rigidbody->acceleration - vec2{0,player->moveSpeed};
        if (right)rigidbody->acceleration = rigidbody->acceleration + vec2{player->moveSpeed,0};
        if (left) rigidbody->acceleration = rigidbody->acceleration - vec2{player->moveSpeed,0};
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        arm->rotation= atan2(mousePos.y-transform->pos.y,mousePos.x-transform->pos.x);
    }
}



