#pragma once
#include "ISystem.h"
#include "../Components/CBoxCollider.h"
#include "../Components/CCapsuleCollider.h"
#include "../Components/CCircleCollider.h"
#include "../Components/CPlaneCollider.h"
#include "../Components/CPlayer.h"
#include "../Components/CRigidbody.h"
#include "../Components/CTransform.h"
#include "../Components/CRender.h"
#include "../Core/Scene.h"
class SPhysics : public ISystem
{
public:
    void Update(Scene* scene);

private:
    //create an array of current collisions
    bool BoxBox(CBoxCollider box1, CTransform tf1, CBoxCollider box2, CTransform tf2);
    bool BoxCircle(CBoxCollider box, CTransform tf1, CCircleCollider circle,CTransform tf2);
    bool BoxCapsule(CBoxCollider box, CTransform tf1, CCapsuleCollider capsule, CTransform tf2);
    bool BoxPlane(CBoxCollider box, CTransform tf1, CPlaneCollider plane, CTransform tf2);

    bool CircleCircle(CCircleCollider circle1, CTransform tf1,CCircleCollider circle2, CTransform tf2);
    bool CircleCapsule(CCircleCollider circle, CTransform tf1, CCapsuleCollider capsule, CTransform tf2);
    bool CirclePlane(CCircleCollider circle, CTransform tf1, CPlaneCollider plane, CTransform tf2);

    bool CapsuleCapsule(CCapsuleCollider capsule1, CTransform tf1, CCapsuleCollider capsule2, CTransform tf2);
    bool CapsulePlane(CCapsuleCollider capsule, CTransform tf1, CPlaneCollider plane, CTransform tf2);
    
    void addImpulse(vec2 direction, CRigidbody body);
};
