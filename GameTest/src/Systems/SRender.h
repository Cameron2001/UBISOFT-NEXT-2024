#pragma once
#include "ISystem.h"

#include "../Components/Components.h"
#include "../Core/Registry.h"

class SRender: public ISystem
{
public:
    void update(Registry& Registry);
private:
    void drawShapes(Registry& Registry);
    void drawSquare(vec2 pos, vec2 extents, vec3 Outcolor={1.0,1.0,1.0});
    void drawCircle(vec2 centre, float radius, int segments = 12,  vec3 Outcolor={1.0,1.0,1.0});
    void drawLabels(Registry& Registry);
    void drawArms(Registry& Registry);
};
