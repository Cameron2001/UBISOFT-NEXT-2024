#include "stdafx.h"
#include "SPlayer.h"

#include "../../App/app.h"
#include "../Core/Factory.h"


void SPlayer::update(Registry& registry, float dt)
{
    for(const auto entityID : registry.getEntities<CPlayer>())
    {
        const CTransform& transform = registry.getComponent<CTransform>(entityID);
        CPlayer& player = registry.getComponent<CPlayer>(entityID);
        CRigidbody& rigidbody = registry.getComponent<CRigidbody>(entityID);
        CArm& arm = registry.getComponent<CArm>(entityID);
        CShield& shield = registry.getComponent<CShield>(entityID);
        bool up = App::IsKeyPressed('W');
        bool down = App::IsKeyPressed('S');
        bool left = App::IsKeyPressed('A');
        bool right = App::IsKeyPressed('D');
        arm.bShoot = App::IsKeyPressed(VK_LBUTTON);
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



