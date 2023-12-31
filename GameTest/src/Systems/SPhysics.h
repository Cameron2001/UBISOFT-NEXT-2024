#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"
struct Collision
{
    Entity entityA;
    Entity entityB;
    vec2 mtv;
    Collision(Entity a, Entity b, vec2 minimumTranslation = {0,0}): entityA(a), entityB(b), mtv(minimumTranslation){};
};
class SPhysics : public ISystem
{
public:
    void Update(Scene* scene, float dt);

private:
    //create an array of current collisions
    bool BoxBox(Scene* scene, Entity aID, Entity bID);
    bool BoxBox(CBoxCollider box1, CTransform tf1, CBoxCollider box2, CTransform tf2);
    bool BoxCircle(CBoxCollider box, CTransform tf1, CCircleCollider circle,CTransform tf2);
    bool BoxCircle(Scene* scene, Entity boxID, Entity circleID);
    bool BoxPlane(CBoxCollider box, CTransform tf1, CPlaneCollider plane, CTransform tf2);
    bool BoxPlane(Scene* scene, Entity boxID, Entity planeID);

    bool CircleCircle(CCircleCollider circle1, CTransform tf1,CCircleCollider circle2, CTransform tf2);
    bool CircleCircle(Scene* scene, Entity aID, Entity bID);
    bool CirclePlane(CCircleCollider circle, CTransform tf1, CPlaneCollider plane, CTransform tf2);
    bool CirclePlane(Scene* scene, Entity circleID, Entity planeID);

    void ResolveCollisions(Scene* scene);

    void CheckCollisions(Scene* scene);
    bool CheckCollision(Scene* scene, Entity a, Entity b);
    void ApplyKinematics(Scene* scene, float dt);

    std::vector<Collision> collisions;
    vec2 gravity = {0,0};
};

