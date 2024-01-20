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
    int ammo;
    float rot;
    float timer = 0.0f;
    float damageScale = 1.0f;
    float aimLength = 100.0f;
    float shootCooldown= 2.0f;
    CPlayer(int a,float speed=300, float rotation = 0):moveSpeed(speed),ammo(a),rot(rotation){}
};
