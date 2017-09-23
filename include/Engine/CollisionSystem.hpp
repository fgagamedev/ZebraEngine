/**
    @file CollisionSystem.hpp
    @brief Manage the collisions between objects in the game.
    @copyright MIT License.
*/

#ifndef __COLLISION_SYSTEM__
#define __COLLISION_SYSTEM__

#include "Engine/SceneManager.hpp"

#include "Components/CircleCollider.hpp"
#include "Components/Collider.hpp"
#include "Components/RectangleCollider.hpp"
#include "Log/log.hpp"
#include "Math/Vector.hpp"

#include <math.h>
#include <vector>

using namespace std;

class CollisionSystem {
public:
    static CollisionSystem *GetInstance();
    void Update();

private:
    CollisionSystem();
    void DetectCollisions();
    void PushColliders();
    void CircleCircle(CircleCollider *circle1, CircleCollider *circle2);
    void RectRect(RectangleCollider *rectangle1, RectangleCollider *rectangle2);
    void CircleRect(CircleCollider *circle, RectangleCollider *rectangle);

    // Pointer that instantiates. Collision system type.
    static CollisionSystem *m_instance;

    // Local vector guarding collisions.
    vector<Collider *> m_colliders;
};

#endif
