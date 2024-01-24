//------------------------------------------------------------------------
// SRender.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ISystem.h"
#include "../Util/Vectors.h"
#include "../Core/Registry.h"

//------------------------------------------------------------------------
class SRender : public ISystem
{
public:
    static void update(Registry& registry);

private:
    static void drawShapes(Registry& registry);
    static void drawSquare(vec2 pos, vec2 extents, vec3 color = {1.0f, 1.0f, 1.0f});
    static void drawCircle(vec2 centre, float radius, int segments = 12, vec3 color = {1.0f, 1.0f, 1.0f});
    static void drawLabels(Registry& registry);
    static void drawArms(Registry& registry);
};
