#include "stdafx.h"
#include "SButton.h"

#include "../../App/app.h"
#include "../Components/Components.h"
#include "../Core/PlayScene.h"
#include "../Core/SceneManager.h"


void SButton::Update(Registry& Registry)
{
   CheckClicks(Registry);
   ResolveClicks(Registry); 
}

void SButton::CheckClicks(Registry& Registry)
{
    
    for (auto entityID : Registry.GetEntities<CButton>())
    {
        const CTransform* transform = Registry.GetComponent<CTransform>(entityID);
        CButton* button = Registry.GetComponent<CButton>(entityID);
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        button->isClicked=Clicked(mousePos, transform->pos,button->bounds);
    }
}

void SButton::ResolveClicks(Registry& Registry)
{
    for (const auto entityID : Registry.GetEntities<CButton>())
    {
        const CButton* button = Registry.GetComponent<CButton>(entityID);
        if(button->isClicked)
        {
            switch (button->type)
            {
            case CButton::ButtonTypes::START:
                StartClick();
                break;
            case CButton::ButtonTypes::EXIT:
                ExitClick();
                break;
            }
        }
        
    }
}

void SButton::StartClick()
{
    SceneManager::GetInstance()->LoadScene<PlayScene>();
}


void SButton::ExitClick()
{
    exit(0);
}


bool SButton::Clicked(vec2 mousePos, vec2 buttonPos, vec2 bounds)
{
    return(mousePos.x>buttonPos.x-bounds.x
        && mousePos.x<buttonPos.x+bounds.x
        && mousePos.y>buttonPos.y-bounds.y
        && mousePos.y<buttonPos.y+bounds.y&&App::IsKeyPressed(VK_LBUTTON));
}
