#include "stdafx.h"
#include "SArm.h"

#include "../Core/Factory.h"
#include "../Util/Utils.h"

void SArm::update(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CArm>())
    {
        CTimer& timer = registry.getComponent<CTimer>(ID);
        CArm& arm = registry.getComponent<CArm>(ID);
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        const CCircleCollider& circle = registry.getComponent<CCircleCollider>(ID);
        const vec2 armStart = transform.pos+circle.offset;
        const bool isPlayer = registry.hasComponent<CPlayer>(ID);
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
                const float multipler = Utils::clamp(timer.timer,0.5f,2.0f);
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
