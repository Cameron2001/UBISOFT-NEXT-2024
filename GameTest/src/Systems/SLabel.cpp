#include "stdafx.h"
#include "SLabel.h"

#include "../../App/app.h"
#include "../Components/CHealth.h"
#include "../Components/CLabel.h"
#include "../Components/CTransform.h"

void SLabel::Update(Scene& scene)
{
    auto labels = scene.reg.GetEntities<CLabel,CTransform>();
    
    for (const auto current : labels)
    {
        const CLabel* label = scene.reg.GetComponent<CLabel>(current);
        const CTransform* transform = scene.reg.GetComponent<CTransform>(current);
        App::Print(transform->pos.x+label->labelOffset.x,transform->pos.y+label->labelOffset.y,label->labelText,25,25,25);
    }
}
