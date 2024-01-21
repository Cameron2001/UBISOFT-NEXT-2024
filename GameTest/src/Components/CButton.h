//------------------------------------------------------------------------
// CButton.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CButton
{
    enum class ButtonTypes
    {
        START,
        EXIT
    };
    ButtonTypes type;
    vec2 bounds;
    bool bClicked = false;
    CButton(ButtonTypes type , vec2 bounds):bounds(bounds),type(type){} 
};