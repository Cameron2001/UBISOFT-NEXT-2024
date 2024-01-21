#pragma once
struct CCircleCollider
{
    float radius;
    vec2 offset;
    int segments;
    CCircleCollider(float rad,int segments = 10, vec2 offset = {0.0f,0.0f}):radius(rad),offset(offset),segments(segments){}
};
