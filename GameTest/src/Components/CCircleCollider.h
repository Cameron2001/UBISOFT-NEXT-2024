#pragma once
struct CCircleCollider
{
    float radius;
    bool isVisible = false;
    bool isTrigger = false;
    CCircleCollider(float rad):radius(rad){}
};
