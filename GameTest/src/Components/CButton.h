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
    bool bClicked;
    CButton(
        ButtonTypes type,
        vec2 bounds
        ):
        type(type),
        bounds(bounds),
        bClicked(false)
    {} 
};