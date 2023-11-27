#pragma once
#include "../Util/Vectors.h"

struct Camera
{
    Camera();

    vec2 position;
    float rotation;

    void Update();
};
