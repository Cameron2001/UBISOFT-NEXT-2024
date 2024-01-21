#include "stdafx.h"
#include "SArm.h"

#include "../Components/Components.h"
#include "../../app/AppSettings.h"
#include "../Core/Factory.h"
#include "../Util/Utils.h"

void SArm::Update(Registry& Registry)
{
    for (auto element : Registry.GetEntities<CArm>())
    {
        CTimer* timer = Registry.GetComponent<CTimer>(element);
        CArm* arm = Registry.GetComponent<CArm>(element);
        const CTransform* transform = Registry.GetComponent<CTransform>(element);
        const CCircleCollider* circle = Registry.GetComponent<CCircleCollider>(element);
        const vec2 armStart = transform->pos+circle->offset;
        bool isPlayer = Registry.HasComponent<CPlayer>(element);
        if(!isPlayer && arm->state==CArm::ArmState::IDLE) arm->shoot = true;
        if(!isPlayer && arm->state==CArm::ArmState::SHOOTING && timer->timer>arm->coolDown/4) arm->shoot = false;
        
        if(arm->state == CArm::ArmState::IDLE && arm->shoot)
        {
            arm->state = CArm::ArmState::SHOOTING;
            timer->timer = 0;
        }
        if(arm->state == CArm::ArmState::SHOOTING)
        {
            if(arm->shoot == false)
            {
                float multipler = Utils::Clamp(timer->timer,0.5f,2.0f);
                Factory::CreateProjectile(Registry,armStart,arm->projectileRadius*multipler, 10, arm->projectileForce*multipler,arm->rotation,arm->projectileHealth*multipler,arm->projectileDamage*multipler);
                arm->state = CArm::ArmState::RELOADING;
                timer->timer = 0.0f;
            }
        }
        if(arm->state == CArm::ArmState::RELOADING)
        {
            
            if(timer->timer>arm->coolDown)
            {
                
                arm->state = CArm::ArmState::IDLE;
                timer->timer = 0.0f;
            }
        }
    }
}
