//------------------------------------------------------------------------
// CCircleCollider.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CCircleCollider
{
    float radius;
    vec2 offset;
    //Number of sides of circle
    int segments;

    CCircleCollider(
        const float radius,
        const int segments = 10,
        const vec2 offset = {0.0f, 0.0f}
    ):
        radius(radius),
        offset(offset),
        segments(segments)
    {
    }
};
