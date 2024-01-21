#include "stdafx.h"
#include "SButton.h"

#include "../../App/app.h"
#include "../Components/Components.h"
#include "../Core/PlayScene.h"
#include "../Core/SceneManager.h"


void SButton::update(Registry& registry)
{
   checkClicks(registry);
   resolveClicks(registry); 
}

void SButton::checkClicks(Registry& registry)
{
    
    for (const Entity ID : registry.getEntities<CButton>())
    {
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        CButton& button = registry.getComponent<CButton>(ID);
        vec2 mousePos;
        App::GetMousePos(mousePos.x,mousePos.y);
        button.isClicked=clicked(mousePos, transform.pos,button.bounds);
    }
}

void SButton::resolveClicks(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CButton>())
    {
        const CButton& button = registry.getComponent<CButton>(ID);
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
