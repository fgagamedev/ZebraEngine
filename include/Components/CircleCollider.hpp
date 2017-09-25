/**
    @file CircleCollider.hpp
    @brief Responsible for managing the animation of a collision.
    @copyright MIT License.
*/

#ifndef __CIRCLE_COLLIDER__
#define __CIRCLE_COLLIDER__

#include "Engine/GameObject.hpp"

#include "Components/Collider.hpp"
#include "Math/Shapes.hpp"
#include "Math/Vector.hpp"

#include <string>

using namespace std;

class CircleCollider : public Collider {
    public:
        CircleCollider(GameObject *owner, Vector &offset, float radius, int layer);
        Vector GetCenter() {
            return Vector(m_shape.x, m_shape.y);
        };

        float GetRadius() {
            return m_shape.radius;
        };

        void FixedComponentUpdate() override;

        virtual string GetComponentName() override {
            return "CircleCollider";
        };

    private:
        // Store the size and position of a circle envolved in a collision.
        Circle m_shape;
        // Store the offset of the circle after the collision.
        Vector m_offset;
};

#endif
