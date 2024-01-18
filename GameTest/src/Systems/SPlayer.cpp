#include "stdafx.h"
#include "SPlayer.h"

#include "SFactory.h"
#include "../../App/app.h"
#include "../Components/CImpulseEvent.h"
#include "../Util/Utils.h"


void SPlayer::Init(Scene& scene)
{
}

void SPlayer::Update(Scene& scene, float dt)
{
    for(auto entityID : scene.reg.GetEntities<CPlayer>())
    {
        //CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        CPlayer* player = scene.reg.GetComponent<CPlayer>(entityID);
        CRigidbody* rigidbody = scene.reg.GetComponent<CRigidbody>(entityID);
        CLabel* label = scene.reg.GetComponent<CLabel>(entityID);
        CHealth* health = scene.reg.GetComponent<CHealth>(entityID);
        
        bool up = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false) || App::IsKeyPressed('W');
        bool down = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false) || App::IsKeyPressed('S');
        bool left = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false) || App::IsKeyPressed('A');
        bool right = App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false) || App::IsKeyPressed('D');
        bool shoot  = App::IsKeyPressed(VK_SPACE);
        bool turnLeft = App::IsKeyPressed('Q');
        bool turnRight = App::IsKeyPressed('E');
        //char buf[1000];
        //sprintf(buf,"%f", health->health);
        //label->labelText = buf;
        

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
        if(shoot && !shot)
        {
            //figure out some off set to make it not spawn on player
            scene.reg.GetSystem<SFactory>()->CreateProjectile(scene,{200,200},10,{1,0},10000);
            shot = true;
        }
        if(turnLeft)
        {
            scene.reg.GetSystem<SFactory>()->CreateAngularImpulseEvent(scene,entityID,100);
        }
        if(turnRight)
        {
            scene.reg.GetSystem<SFactory>()->CreateAngularImpulseEvent(scene,entityID,-100);
        }
        
        //scene->m_register.GetComponent<CTransform>(m_camera)->pos={transform->pos.x-APP_VIRTUAL_WIDTH/2,transform->pos.y-APP_VIRTUAL_HEIGHT/2};
        //auto cam = scene.reg.GetEntities<CCamera>();
        //CTransform* tf = scene.reg.GetComponent<CTransform>(cam[0]);
        //tf->pos=Utils::Lerp(scene.reg.GetComponent<CTransform>(cam[0])->pos,{transform->pos.x-APP_VIRTUAL_WIDTH/2,transform->pos.y-APP_VIRTUAL_HEIGHT/2},0.1);
        //.pos=Utils::Lerp(scene.reg.GetComponent<CTransform>(m_camera).pos,{transform.pos.x-APP_VIRTUAL_WIDTH/2,transform.pos.y-APP_VIRTUAL_HEIGHT/2},0.1);
    }
}



