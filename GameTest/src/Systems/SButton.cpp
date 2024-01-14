#include "stdafx.h"
#include "SButton.h"

#include "../../App/app.h"
#include "../Components/Components.h"


void SButton::Update(Scene& scene, float dt)
{
    for (auto entityID : scene.reg.GetEntities<CButton>())
    {
        CTransform& transform = scene.reg.GetComponent<CTransform>(entityID);
        CBoxCollider& box = scene.reg.GetComponent<CBoxCollider>(entityID);
        /*float mouseX;
        float mouseY;
        App::GetMousePos(mouseX,mouseY);
        auto buttonClick = scene.reg.CreateEntity();
        scene->reg.AddComponent(buttonClick,CButtonClickEvent());*/
    }
}
