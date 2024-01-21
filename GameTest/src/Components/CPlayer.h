#pragma once

struct CPlayer
{
    enum class States
    {
        IDLE,
        SHOOTING,
        RELOADING
    };
    States state = States::IDLE;
    float moveSpeed;
    float damageScale = 1.0f;
    float shootCooldown= 1.0f;
    CPlayer(float speed=300, float rotation = 0):moveSpeed(speed){}
};
