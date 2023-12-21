#pragma once
#include "ISystem.h"

#include "../Components/CPlayer.h"
#include "../Components/CRigidbody.h"
#include "../Components/CTransform.h"
#include "../Components/CRender.h"
#include "../Core/Scene.h"

class SRender: public ISystem
{
public:
    void Update(Scene* scene);
    void DrawSquare(float xMin,float yMin, float xMax, float yMax);
    
};
