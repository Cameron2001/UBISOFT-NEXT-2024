#pragma once
#include "ISystem.h"

#include "../Components/Components.h"
#include "../Core/Registry.h"

class SRender: public ISystem
{
public:
    void Update(Registry& Registry);
private:
    void DrawShapes(Registry& Registry);
    void DrawSquare(vec2 pos, vec2 extents, vec3 Outcolor={1.0,1.0,1.0});
    void DrawCircle(vec2 centre, float radius, int segments = 12,  vec3 Outcolor={1.0,1.0,1.0});
    void DrawLabels(Registry& Registry);
    void DrawArms(Registry& Registry);
    void DrawUI(Registry& scene);
};
