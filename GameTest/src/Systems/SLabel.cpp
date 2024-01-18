#include "stdafx.h"
#include "SLabel.h"

#include "../../App/app.h"
#include "../Components/CColor.h"
#include "../Components/CHealth.h"
#include "../Components/CLabel.h"
#include "../Components/CTransform.h"

void SLabel::Update(Scene& scene)
{
    auto labels = scene.reg.GetEntities<CLabel>();
    for (auto current : labels)
    {
        CLabel* label = scene.reg.GetComponent<CLabel>(current);
        CTransform* transform = scene.reg.GetComponent<CTransform>(current);
        if(scene.reg.HasComponent<CColor>(current))
        {
            CColor* colorComp = scene.reg.GetComponent<CColor>(current);
            App::Print(transform->pos.x,transform->pos.y,label->labelText,colorComp->rgbValue.x,colorComp->rgbValue.y,colorComp->rgbValue.z);
        }
        else
        {
            App::Print(transform->pos.x,transform->pos.y,label->labelText,25,25,25);
        }
    }
}
