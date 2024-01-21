#pragma once
#include "ISystem.h"

#include "../Components/Components.h"
#include "../Core/Scene.h"

class SRender: public ISystem
{
public:
    void Update(Scene& scene);
private:
    void DrawPlayer(Scene& scene);
    void DrawTank(Scene& scene);
    void DrawSquare(vec2 pos, vec2 extents, vec3 Outcolor={1.0,1.0,1.0});
    void DrawCircle(vec2 centre, float radius, int segments = 12,  vec3 Outcolor={1.0,1.0,1.0});
    void DrawLabels(Scene& scene);
    void DrawUI(Scene& scene);
};
