#include "stdafx.h"
#include "SButton.h"

#include "../../App/app.h"
#include "../Components/Components.h"


void SButton::Update(Scene& scene)
{
   CheckClicks(scene);
   ResolveClicks(scene); 
}

void SButton::CheckClicks(Scene& scene)
{
    
    for (auto entityID : scene.reg.GetEntities<CButton,CTransform>())
    {
        CTransform* transform = scene.reg.GetComponent<CTransform>(entityID);
        CButton* button = scene.reg.GetComponent<CButton>(entityID);
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        button->isClicked=Clicked(mousePos, transform->pos,button->bounds);
    }
}

void SButton::ResolveClicks(Scene& scene)
{
    for (auto entityID : scene.reg.GetEntities<CButton,CTransform>())
    {
        CButton* button = scene.reg.GetComponent<CButton>(entityID);
        if(button->isClicked)
        {
            
            switch (button->type)
            {
            case CButton::ButtonTypes::START:
                StartClick(scene);
                break;
            case CButton::ButtonTypes::EXIT:
                ExitClick(scene);
                break;
            case CButton::ButtonTypes::RETRY:
                RetryClick(scene);
                break;
            case CButton::ButtonTypes::TUTORIAL:
                TutorialClick(scene);
                break;
            }
        }
        
    }
}

void SButton::StartClick(Scene& scene)
{
    
}

void SButton::TutorialClick(Scene& scene)
{
    
}

void SButton::ExitClick(Scene& scene)
{
    exit(0);
}

void SButton::RetryClick(Scene& scene)
{
}

bool SButton::Clicked(vec2 mousePos, vec2 buttonPos, vec2 bounds)
{
    return(mousePos.x>buttonPos.x-bounds.x
        && mousePos.x<buttonPos.x+bounds.x
        && mousePos.y>buttonPos.y-bounds.y
        && mousePos.y<buttonPos.y+bounds.y&&App::IsKeyPressed(VK_LBUTTON));
}
