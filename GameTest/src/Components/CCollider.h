#pragma once
struct CCollider
{
    bool isTrigger;
    CCollider(bool trigger = false): isTrigger(trigger){}
};
