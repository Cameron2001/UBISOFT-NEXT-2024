//------------------------------------------------------------------------
// CArm.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Util/Utils.h"

//------------------------------------------------------------------------
struct CArm
{
    //States the arm can have
    enum class ArmState
    {
        SHOOTING,
        RELOADING,
        IDLE
    };

    //Properties of arm
    ArmState state;
    float rotation;
    float armLength;
    float coolDown;

    //Properties of projectile being created
    float projectileForce;
    float projectileRadius;
    float projectileHealth;
    float projectileDamage;

    vec3 color;
    bool bShoot;

    CArm(
        const float armLength = 30.0f,
        const float force = 30000.0f,
        const float health = 50.0f,
        const float damage = 35.0f,
        const float radius = 15.0f,
        const float coolDown = 3.0f
    ):
        state(ArmState::IDLE),
        rotation(0.0f),
        armLength(armLength),
        coolDown(coolDown),
        projectileForce(force),
        projectileRadius(radius),
        projectileHealth(health),
        projectileDamage(damage),
        color({1.0f, 1.0f, 1.0f}),
        bShoot(false)
    {
    }
};
