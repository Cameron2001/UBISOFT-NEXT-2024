#include "stdafx.h"
#include "SArm.h"

#include "../Core/Factory.h"
#include "../Util/Utils.h"

void SArm::update(Registry& registry)
{
    for (auto element : registry.getEntities<CArm>())
    {
        CTimer& timer = registry.getComponent<CTimer>(element);
        CArm& arm = registry.getComponent<CArm>(element);
        const CTransform& transform = registry.getComponent<CTransform>(element);
        const CCircleCollider& circle = registry.getComponent<CCircleCollider>(element);
        const vec2 armStart = transform.pos+circle.offset;
        bool isPlayer = registry.hasComponent<CPlayer>(element);
        if(!isPlayer && arm.state==CArm::ArmState::IDLE) arm.bShoot = true;
        if(!isPlayer && arm.state==CArm::ArmState::SHOOTING && timer.timer>arm.coolDown/4) arm.bShoot = false;
        
        if(arm.state == CArm::ArmState::IDLE && arm.bShoot)
        {
            arm.state = CArm::ArmState::SHOOTING;
            timer.timer = 0;
        }
        if(arm.state == CArm::ArmState::SHOOTING)
        {
            if(arm.bShoot == false)
            {
                float multipler = Utils::Clamp(timer.timer,0.5f,2.0f);
                Factory::createProjectile(registry,armStart,arm.projectileRadius*multipler, 10, arm.projectileForce*multipler,arm.rotation,arm.projectileHealth*multipler,arm.projectileDamage*multipler);
                arm.state = CArm::ArmState::RELOADING;
                timer.timer = 0.0f;
            }
        }
        if(arm.state == CArm::ArmState::RELOADING)
        {
            
            if(timer.timer>arm.coolDown)
            {
                
                arm.state = CArm::ArmState::IDLE;
                timer.timer = 0.0f;
            }
        }
    }
}
