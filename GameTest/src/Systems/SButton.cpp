//------------------------------------------------------------------------
// SButton.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "SButton.h"
//------------------------------------------------------------------------
#include "../../App/app.h"
#include "../Components/Components.h"
#include "../Core/PlayScene.h"
#include "../Core/SceneManager.h"
//------------------------------------------------------------------------

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
        button.bClicked=clicked(mousePos, transform.pos,button.bounds);
    }
}

void SButton::resolveClicks(Registry& registry)
{
    for (const Entity ID : registry.getEntities<CButton>())
    {
        const CButton& button = registry.getComponent<CButton>(ID);
        if(!button.bClicked) continue;
        
        switch (button.type)
        {
        case CButton::ButtonTypes::START:
            SceneManager::getInstance()->loadScene<PlayScene>();
            break;
        case CButton::ButtonTypes::EXIT:
            exit(0);
        }
    }
}

bool SButton::clicked(vec2 mousePos, vec2 buttonPos, vec2 bounds)
{
    return mousePos.x>buttonPos.x-bounds.x
        && mousePos.x<buttonPos.x+bounds.x
        && mousePos.y>buttonPos.y-bounds.y
        && mousePos.y<buttonPos.y+bounds.y
        &&App::IsKeyPressed(VK_LBUTTON);
}
