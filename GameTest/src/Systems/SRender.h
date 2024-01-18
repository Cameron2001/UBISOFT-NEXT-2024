#pragma once
#include "ISystem.h"

#include "../Components/Components.h"
#include "../Core/Scene.h"

class SRender: public ISystem
{
public:
    void Init(Scene& scene);
    void Update(Scene& scene);
    void DrawSquare(vec2 pos, vec2 extents,float rotation = 0, vec3 color={255,255,255});
    void DrawCircle(vec2 centre, float radius, int segments = 16, vec3 color={255,255,255});
    CTransform* cameraTransform;
};
