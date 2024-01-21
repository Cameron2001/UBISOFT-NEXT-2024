#include "stdafx.h"
#include "SButton.h"

#include "../../App/app.h"
#include "../Components/Components.h"
#include "../Core/PlayScene.h"
#include "../Core/SceneManager.h"


void SButton::update(Registry& Registry)
{
   checkClicks(Registry);
   resolveClicks(Registry); 
}

void SButton::checkClicks(Registry& Registry)
{
    
    for (auto entityID : Registry.getEntities<CButton>())
    {
        const CTransform& transform = Registry.getComponent<CTransform>(entityID);
        CButton& button = Registry.getComponent<CButton>(entityID);
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        button.isClicked=clicked(mousePos, transform.pos,button.bounds);
    }
}

void SButton::resolveClicks(Registry& Registry)
{
    for (const auto entityID : Registry.getEntities<CButton>())
    {
        const CButton& button = Registry.getComponent<CButton>(entityID);
        if(button.isClicked)
        {
            switch (button.type)
            {
            case CButton::ButtonTypes::START:
                startClick();
                break;
            case CButton::ButtonTypes::EXIT:
                exitClick();
                break;
            }
        }
        
    }
}

void SButton::startClick()
{
    SceneManager::getInstance()->loadScene<PlayScene>();
}


void SButton::exitClick()
{
    exit(0);
}


bool SButton::clicked(vec2 mousePos, vec2 buttonPos, vec2 bounds)
{
    return(mousePos.x>buttonPos.x-bounds.x
        && mousePos.x<buttonPos.x+bounds.x
        && mousePos.y>buttonPos.y-bounds.y
        && mousePos.y<buttonPos.y+bounds.y&&App::IsKeyPressed(VK_LBUTTON));
}
