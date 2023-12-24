#pragma once
#include "ISystem.h"

#include "../Components/Components.h"
#include "../Core/Scene.h"

class SRender: public ISystem
{
public:
    void Update(Scene* scene);
    void DrawSquare(float xMin,float yMin, float xMax, float yMax);
    
};
