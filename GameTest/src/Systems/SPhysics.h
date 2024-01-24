//------------------------------------------------------------------------
// SPhysics.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ISystem.h"
#include "../Core/Registry.h"

//------------------------------------------------------------------------
class SPhysics : public ISystem
{
public:
    static void update(Registry& registry, float dt);

private:
    //create an array of current collisions
    static bool boxBox(Registry& registry, Entity aID, Entity bID);
    static bool boxCircle(Registry& registry, Entity boxID, Entity circleID);
    static bool circleCircle(Registry& registry, Entity aID, Entity bID);
    static void resolveCollisions(Registry& registry);
    static void checkCollisions(Registry& registry);
    static bool checkCollision(Registry& registry, Entity a, Entity b);
    static void applyKinematics(Registry& registry, float dt);
    static void deleteOffscreen(Registry& registry);
};
