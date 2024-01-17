#pragma once
struct CCamera
{
    float rotation;
    float zoom;
    CCamera(float rot = 0, float z = 0): rotation(rot),zoom(z){}
};