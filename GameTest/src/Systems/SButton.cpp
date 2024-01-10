#include "stdafx.h"
#include "SButton.h"

#include "../../App/app.h"
#include "../Components/CBoxCollider.h"
#include "../Components/CButton.h"
#include "../Components/CButtonClickEvent.h"

void SButton::Update(Scene* scene, float dt)
{
    for (auto entityID : scene->reg.GetEntities<CButton>())
    {
        auto transform = scene->reg.GetComponent<CTransform>(entityID);
        auto box = scene->reg.GetComponent<CBoxCollider>(entityID);
        /*float mouseX;
        float mouseY;
        App::GetMousePos(mouseX,mouseY);
        auto buttonClick = scene->reg.CreateEntity();
        scene->reg.AddComponent(buttonClick,CButtonClickEvent());*/
    }
}
