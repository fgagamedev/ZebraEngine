/**
    @file CollisionSystem.cpp
    @brief Manage the collisions between objects in the game.
    @copyright MIT License.
*/
#include "Engine/CollisionSystem.hpp"

#include <math.h>

//Initializes the instance pointer of type Collision System as nullptr.
CollisionSystem *CollisionSystem::m_instance = nullptr;

/**
    @brief Constructor for the class CollisionSystem.
*/
CollisionSystem::CollisionSystem() {

}

/**
    @brief Give a CollisionSystem's object.
    @return The existing or new object of CollisionSystem.
*/
CollisionSystem *CollisionSystem::GetInstance() {
    // Checks if the collision system was instantiated, if not, instantiates it.
    if (!m_instance) {
        m_instance = new CollisionSystem();
    }
    return m_instance;
}

void CollisionSystem::Update() {
    PushColliders();
    DetectCollisions();
}

/**
    @brief Determine if collisions between elements have happened.
*/
void CollisionSystem::DetectCollisions() {
    // Defines the boundaries as trees and walls.

    // Runs through the vector of collisions
    for (int i = 0; i < m_colliders.size(); i++) {
        for (int k = i + 1; k < m_colliders.size(); k++) {
            // Checks the components names, if its circle collider, sets both colliders as circle colliders.
            if (m_colliders[i]->GetComponentName() == m_colliders[k]->GetComponentName()
                && m_colliders[i]->GetComponentName() == "CircleCollider") {
                    CircleCircle((CircleCollider *)m_colliders[i],
                                (CircleCollider *)m_colliders[k]);
            // Checks the components names, if its rectangle collider, sets both colliders as rectangle colliders.
            } else if (m_colliders[i]->GetComponentName() == m_colliders[k]->GetComponentName()
                       && m_colliders[i]->GetComponentName() == "RectangleCollider") {
                    RectRect((RectangleCollider *)m_colliders[i],
                             (RectangleCollider *)m_colliders[k]);
            // Checks the components names, if its circle and rectangle colliders, sets both colliders.
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

    // Runs through all gameobjects.
    for (auto gameobject : gameobjects) {
        // Gets all gameobjects.
        for (auto key : gameobject->GetAllComponents()) {
            // Checks if the first key is not of physics.
            if (key.first != C_PHYSICS) {
                break;
            }
            for (auto element : key.second) {
                // Checks the component name, if its circle or rectangle colliders, sets the colliders at the end of the vector.
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
    @param[in/out] circle1 Object of type CircleCollider class.
    @param[in/out] circle2 Object of type CircleCollider class.
*/
void CollisionSystem::CircleCircle(CircleCollider *circle1, CircleCollider *circle2) {

    // Boolean variable of type true or false that defines collisions.
    bool collision = false;

    auto circle2Center = circle2 -> GetCenter();

    // Compares the distance of the center of the circle.
    if (circle1->GetCenter().GetDistance(circle2Center) <= circle1->GetRadius() + circle2->GetRadius()){
        collision = true;
    }

    // Checks the collision status, and updates it.
    if (collision) {
        circle1->GetOwner()->AddCollision(circle2->GetOwner());
        circle2->GetOwner()->AddCollision(circle1->GetOwner());
    }
}

/**
    @brief Determines if two rectangles collided.
    @param[in] rectangle1 Object of type RectangleCollider class.
    @param[in] rectangle2 Object of type RectangleCollider class.
*/
void CollisionSystem::RectRect(RectangleCollider *rectangle1, RectangleCollider *rectangle2) {

    // Boolean variable of type true or false that defines collisions.
    bool collision = false;

    auto posR1 = rectangle1->GetRectanglePoint();

    auto posR2 = rectangle2->GetRectanglePoint();

    // Compares the rectangles 1 and 2 positions.
    if (((posR1.m_x <= (posR2.m_x + rectangle2->GetWidth()))
        && ((posR1.m_x + rectangle1->GetWidth()) >= posR2.m_x))
        && ((posR1.m_y <= (posR2.m_y + rectangle2->GetHeight()))
        && ((posR1.m_y + rectangle1->GetHeight()) >= posR2.m_y))
        && (rectangle1->m_owner->active) && (rectangle2->m_owner->active)) {
            collision = true;
    }

    // Checks the collision status, and updates it.
    if (collision) {
        rectangle1->GetOwner()->AddCollision(rectangle2->GetOwner());
        rectangle2->GetOwner()->AddCollision(rectangle1->GetOwner());
    }
}

/**
    @brief Determines if a circle and a rectangle collided.
    @param[in] circle Object of type circleCollider class.
    @param[in] rectangle Object of type RectangleCollider class.
*/
void CollisionSystem::CircleRect(CircleCollider *circle, RectangleCollider *rectangle) {

    // Boolean variable of type true or false that defines collisions.
    bool collision = false;

    // Distance between centers in x-axis.
    double distanceX = abs(circle->GetCenter().m_x - rectangle->GetRectanglePoint().m_x
                           - rectangle->GetWidth() / 2);

    // Distance between centers in y-axis.
    double distanceY = abs(circle->GetCenter().m_y - rectangle->GetRectanglePoint().m_y
                           - rectangle->GetHeight() / 2);

    // Distance between centers  in x-axis.
    double distancex = distanceX - rectangle -> GetWidth() / 2;

    // Distance between centers  in y-axis.
    double distancey = distanceY - rectangle -> GetHeight() / 2;

    /*
        Checks if the distance on x-axis between centers are greater than
        TextWidth divided by 2 in addition to Circle Radius, in that case
        there is in Collision. The same logic is used on y-axis.
    */
    
    // Compares the rectangles distances.
    if (!((distanceX > (rectangle->GetWidth() / 2 + circle->GetRadius()))
        || (distanceY > (rectangle->GetHeight() / 2 + circle->GetRadius())))){
        //nothing to do.
    }

    /*
        Verify if the distance between centers are lesser than rect width and
        height, also checks if the hypotenuse(Line that connects both centers and
        crosses the rect vertice) is lesser than circle radius^2, in that case,
        collision occurs.
    */

    // Compares the rectangle distances.
    if (((distanceX <= (rectangle->GetWidth() / 2)) || (distanceY <= (rectangle -> GetHeight() / 2)))
        || (((distancex * distancex) + (distancey *distancey))
        <= (circle->GetRadius() *circle->GetRadius()))) {
        collision = true;
    }

    // Checks the collision status, and updates it.
    if (collision) {
        circle->GetOwner()->AddCollision(rectangle->GetOwner());
        rectangle->GetOwner()->AddCollision(circle->GetOwner());
    }
}
