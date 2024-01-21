#pragma once
#include "ISystem.h"
#include "../Util/Vectors.h"
#include "../Core/Registry.h"

class SRender: public ISystem
{
public:
    void update(Registry& registry);
private:
    void drawShapes(Registry& registry);
    void drawSquare(vec2 pos, vec2 extents, vec3 Outcolor={1.0,1.0,1.0});
    void drawCircle(vec2 centre, float radius, int segments = 12,  vec3 Outcolor={1.0,1.0,1.0});
    void drawLabels(Registry& registry);
    void drawArms(Registry& registry);
};
