#include "stdafx.h"
#include "SPlayer.h"

#include "../../App/app.h"
#include "../Core/Factory.h"
#include "../Util/Utils.h"


void SPlayer::update(Registry& Registry, float dt)
{
    for(const auto entityID : Registry.getEntities<CPlayer>())
    {
        const CTransform& transform = Registry.getComponent<CTransform>(entityID);
        CPlayer& player = Registry.getComponent<CPlayer>(entityID);
        CRigidbody& rigidbody = Registry.getComponent<CRigidbody>(entityID);
        CArm& arm = Registry.getComponent<CArm>(entityID);
        CShield& shield = Registry.getComponent<CShield>(entityID);
        bool up = App::IsKeyPressed('W');
        bool down = App::IsKeyPressed('S');
        bool left = App::IsKeyPressed('A');
        bool right = App::IsKeyPressed('D');
        arm.shoot = App::IsKeyPressed(VK_LBUTTON);
        shield.isEnabled =  App::IsKeyPressed(VK_SPACE);
        if (up) rigidbody.acceleration  = rigidbody.acceleration+ vec2{0,player.moveSpeed};
        if (down)rigidbody.acceleration = rigidbody.acceleration - vec2{0,player.moveSpeed};
        if (right)rigidbody.acceleration = rigidbody.acceleration + vec2{player.moveSpeed,0};
        if (left) rigidbody.acceleration = rigidbody.acceleration - vec2{player.moveSpeed,0};
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        arm.rotation= atan2(mousePos.y-transform.pos.y,mousePos.x-transform.pos.x);
    }
}



