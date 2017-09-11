#include "Engine/CollisionSystem.hpp"

#include <math.h>

/**
    @file CollisionSystem.cpp
    @brief Manage the collisions between objects in the game.
    @copyright MIT License.
*/

CollisionSystem *CollisionSystem::m_instance = nullptr;

/**
    @brief Constructor for the class CollisionSystem.
*/
CollisionSystem::CollisionSystem() {}

/**
    @brief Give a CollisionSystem's object.
    @return The existing or new object of CollisionSystem.
*/
CollisionSystem *CollisionSystem::GetInstance() {
    if (!m_instance) {
        m_instance = new CollisionSystem();
    }
    return m_instance;
}

/**

*/
void CollisionSystem::Update() {
    PushColliders();
    DetectCollisions();
}

/**
    @brief Determine if collisions between elements have happened.
*/
void CollisionSystem::DetectCollisions() {
    for (int i = 0; i < m_colliders.size(); i++) {
        for (int k = i + 1; k < m_colliders.size(); k++) {
            if (m_colliders[i]->GetComponentName() == m_colliders[k]->GetComponentName()
            && m_colliders[i]->GetComponentName() == "CircleCollider") {
                CircleCircle((CircleCollider *)m_colliders[i],
                             (CircleCollider *)m_colliders[k]);
            } else if (m_colliders[i]->GetComponentName() == m_colliders[k]->GetComponentName()
            && m_colliders[i]->GetComponentName() == "RectangleCollider") {
                RectRect((RectangleCollider *)m_colliders[i],
                         (RectangleCollider *)m_colliders[k]);
            } else if (m_colliders[i]->GetComponentName() != m_colliders[k]->GetComponentName()
            && m_colliders[i]->GetComponentName() == "CircleCollider") {
                CircleRect((CircleCollider *)m_colliders[i],
                           (RectangleCollider *)m_colliders[k]);
            } else {
                CircleRect((CircleCollider *)m_colliders[k],
                           (RectangleCollider *)m_colliders[i]);

            }
        }
    }
}

/**
    @brief Search and storage colliders in the game.
*/
void CollisionSystem::PushColliders() {
    m_colliders.clear();

    auto gameobjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();

    for (auto gameobject : gameobjects) {
        for (auto key : gameobject->GetAllComponents()) {
            if (key.first != C_PHYSICS) {
                break;
            }
            for (auto element : key.second) {
                if (element->GetComponentName() == "CircleCollider"
                || element->GetComponentName() == "RectangleCollider") {
                    m_colliders.push_back((Collider *)element);
                }
            }
        }
    }
}

/**
    @brief Determines if two circles collided.
    @param[in/out] c1
    @param[in/out] c2
*/
void CollisionSystem::CircleCircle(CircleCollider *c1, CircleCollider *c2) {
    bool collision = false;
    auto c2Center = c2->GetCenter();

    if (c1->GetCenter().GetDistance(c2Center) <= c1->GetRadius() + c2->GetRadius()){
        collision = true;
    }

    if (collision) {
        //INFO("CIRCLE CIRCLE");
        //INFO("COLLIDED");
        c1->GetOwner()->AddCollision(c2->GetOwner());
        c2->GetOwner()->AddCollision(c1->GetOwner());
    }
}

/**
    @brief Determines if two rectangles collided.
    @param[in/out] r1
    @param[in/out] r2
*/
void CollisionSystem::RectRect(RectangleCollider *r1, RectangleCollider *r2) {
    bool collision = false;
    auto posR1 = r1->GetRectanglePoint();
    auto posR2 = r2->GetRectanglePoint();

    if (((posR1.m_x <= (posR2.m_x + r2->GetWidth()))
    && ((posR1.m_x + r1->GetWidth())>=posR2.m_x))
    && ((posR1.m_y <=(posR2.m_y + r2->GetHeight()))
    && ((posR1.m_y + r1->GetHeight())>=posR2.m_y))
    && (r1->m_owner->active) && (r2->m_owner->active)) {
        collision=true;
    }

    if (collision) {
        //INFO("COLLIDED");
        //INFO("RECT RECT");
        r1->GetOwner()->AddCollision(r2->GetOwner());
        r2->GetOwner()->AddCollision(r1->GetOwner());
    }
}

/**
    @brief Determines if a circle and a rectangle collided.
    @param[in/out] c
    @param[in/out] r
*/
void CollisionSystem::CircleRect(CircleCollider *c, RectangleCollider *r) {
    bool collision = false;
    //Distance between centers in x-axis
    double distX = abs(c->GetCenter().m_x - r->GetRectanglePoint().m_x
    - r->GetWidth()/2);
    //Distance between centers in y-axis
    double distY = abs(c->GetCenter().m_y - r->GetRectanglePoint().m_y
    - r->GetHeight()/2);
    //Distance between centers  in x-axis
    double dx=distX - r->GetWidth()/2;
    double dy=distY - r->GetHeight()/2;
    /*Checks if the distance on x-axis between centers are greater than
    RectWidth/2 + CircleRadius,in that case there is no Collision.The same logic
    is used on y-axis*/
    if (!((distX > (r->GetWidth()/2 + c->GetRadius()))
    || (distY > (r->GetHeight()/2 + c->GetRadius()) )))
    /*verify if the distance between centers are lesser than rect width and
    height, also checks if the hypotenuse(Line that connects both centers and
    crosses the rect vertice) is lesser than circle radius^2,in that case,
    collision occurs.*/
    if (((distX <= (r->GetWidth()/2))
    || (distY <= (r->GetHeight()/2)))
    || (dx*dx + dy*dy <= (c->GetRadius()*c->GetRadius()))) {
        collision=true;
    }

    if (collision) {
        //INFO("COLLIDED");
        //INFO("RECT CIRCLE");
        c->GetOwner()->AddCollision(r->GetOwner());
        r->GetOwner()->AddCollision(c->GetOwner());
    }

}
