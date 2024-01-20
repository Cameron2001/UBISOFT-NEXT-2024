#pragma once
struct CCircleCollider
{
    float radius;
    vec2 offset;
    bool isTrigger = false;
    CCircleCollider(float rad,vec2 offset = {0.0f,0.0f}):radius(rad),offset(offset){}
};
