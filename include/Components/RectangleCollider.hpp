#ifndef __RECTANGLE_COLLIDER__
#define __RECTANGLE_COLLIDER__

#include "Engine/GameObject.hpp"

#include "Components/Collider.hpp"
#include "Math/Shapes.hpp"
#include "Math/Vector.hpp"

/**
    @file RectangleCollider.hpp
    @brief This class contains all attributes and methods that creates all collisions in-game.
    @copyright LGPL. MIT License.
*/

using namespace std;

class RectangleCollider : public Collider {

public:
    RectangleCollider(GameObject *owner, Vector offset, float width, float height,
                     int layer);

    void FixedComponentUpdate() override;

    Vector GetRectanglePoint() {
        return Vector(m_shape.x, m_shape.y);
    };

    float GetWidth() {
        return m_shape.width;
    };

    float GetHeight() {
        return m_shape.height;
    };
    
    virtual string GetComponentName() override {
        return "RectangleCollider";
    };
    GameObject *m_owner;

private:
    Rectangle m_shape;
    Vector m_offset;
};

#endif // __RECTANGLE_COLLIDER__