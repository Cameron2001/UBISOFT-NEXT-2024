#pragma once
struct CButton
{
    enum class ButtonTypes
    {
        START,
        EXIT
    };
    ButtonTypes type;
    vec2 bounds;
    bool isClicked = false;
    CButton(ButtonTypes buttonType , vec2 buttonBounds):bounds(buttonBounds),type(buttonType){} 
};