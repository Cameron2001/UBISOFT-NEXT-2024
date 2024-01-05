#pragma once
#include "../Util/Vectors.h"
struct CImpulseEvent
{
    vec2 direction;
    float force;
    Entity target;
    CImpulseEvent(Entity trgt, vec2 dir, float f):target(trgt),direction(dir),force(f){}
};
