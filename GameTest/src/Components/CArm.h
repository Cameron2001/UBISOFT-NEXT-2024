﻿//------------------------------------------------------------------------
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
        float armLength = 30.0f,
        float force = 30000.0f,
        float health = 50.0f,
        float damage = 35.0f,
        float radius = 15.0f,
        float coolDown = 3.0f
        ):
        state(ArmState::IDLE),
        rotation(0.0f),
        armLength(armLength),
        coolDown(coolDown),
        projectileForce(force),
        projectileRadius(radius),
        projectileHealth(health),
        projectileDamage(damage),
        color({1.0f,1.0f,1.0f}),
        bShoot(false)
    {}  
};