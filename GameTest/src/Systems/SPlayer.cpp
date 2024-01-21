#include "stdafx.h"
#include "SPlayer.h"

#include "../../App/app.h"
#include "../Core/Factory.h"


void SPlayer::update(Registry& registry, float dt)
{
    for(const Entity ID : registry.getEntities<CPlayer>())
    {
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        CPlayer& player = registry.getComponent<CPlayer>(ID);
        CRigidbody& rigidbody = registry.getComponent<CRigidbody>(ID);
        CArm& arm = registry.getComponent<CArm>(ID);
        CShield& shield = registry.getComponent<CShield>(ID);
        bool up = App::IsKeyPressed('W');
        bool down = App::IsKeyPressed('S');
        bool left = App::IsKeyPressed('A');
        bool right = App::IsKeyPressed('D');
        arm.bShoot = App::IsKeyPressed(VK_LBUTTON);
        shield.bEnabled =  App::IsKeyPressed(VK_SPACE);
        if (up) rigidbody.acceleration  = rigidbody.acceleration+ vec2{0,player.moveSpeed};
        if (down)rigidbody.acceleration = rigidbody.acceleration - vec2{0,player.moveSpeed};
        if (right)rigidbody.acceleration = rigidbody.acceleration + vec2{player.moveSpeed,0};
        if (left) rigidbody.acceleration = rigidbody.acceleration - vec2{player.moveSpeed,0};
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        arm.rotation= atan2(mousePos.y-transform.pos.y,mousePos.x-transform.pos.x);
    }
}



