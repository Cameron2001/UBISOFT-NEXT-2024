//------------------------------------------------------------------------
// SPlayer.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "SPlayer.h"
//------------------------------------------------------------------------
#include "../../App/app.h"
#include "../Core/Factory.h"
//------------------------------------------------------------------------


void SPlayer::update(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CPlayer>())
    {
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        const CPlayer& player = registry.getComponent<CPlayer>(ID);

        CRigidbody& rigidbody = registry.getComponent<CRigidbody>(ID);
        CArm& arm = registry.getComponent<CArm>(ID);

        arm.bShoot = App::IsKeyPressed(VK_LBUTTON);

        //input and movement
        if (App::IsKeyPressed('W')) rigidbody.acceleration = rigidbody.acceleration + vec2{0.0f, player.moveSpeed}; //UP
        if (App::IsKeyPressed('S'))rigidbody.acceleration = rigidbody.acceleration - vec2{0.0f, player.moveSpeed};
        //DOWN
        if (App::IsKeyPressed('D'))rigidbody.acceleration = rigidbody.acceleration + vec2{player.moveSpeed, 0.0f};
        //RIGHT
        if (App::IsKeyPressed('A')) rigidbody.acceleration = rigidbody.acceleration - vec2{player.moveSpeed, 0.0f};
        //LEFT

        //rotating arm angle to mousePos
        vec2 mousePos;
        App::GetMousePos(mousePos.x, mousePos.y);
        arm.rotation = atan2(mousePos.y - transform.pos.y, mousePos.x - transform.pos.x);
    }
}
