#pragma once
struct CAngularImpulseEvent
{
    Entity target;
    float force;
    CAngularImpulseEvent(Entity trgt, float f): target(trgt), force(f){}
};