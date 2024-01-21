//------------------------------------------------------------------------
// CArm.h
//------------------------------------------------------------------------
#pragma once
#include "../Util/Utils.h"
struct CArm
{
    enum class ArmState
    {
        SHOOTING,
        RELOADING,
        IDLE
    };
    ArmState state;
    float rotation;
    float armLength;
    float coolDown;
    float projectileForce;
    float projectileRadius;
    float projectileHealth;
    float projectileDamage;
    
    vec3 color;
    bool bShoot  = false;
    
    CArm(float armLength = 30.0f, float force = 30000.0f, float health = 50.0f, float damage = 35.0f, float radius = 15.0f, float coolDown = 3.0f):rotation(0.0f),color({1.0f,1.0f,1.0f}),armLength(armLength),projectileForce(force),projectileHealth(health),projectileDamage(damage),projectileRadius(radius),coolDown(coolDown),state(ArmState::IDLE){}
};