/**
    @file CircleCollider.cpp
    @brief Responsible for managing the animation of a collision.
    @copyright MIT License.
*/

#include "Components/CircleCollider.hpp"

/**
    @brief Sets the size of the circle rendered.
    @param[in] owner.
    @param[in] offset.
    @param[in] radius float value to set the radius of the circle.
    @param[in] layer is passed as a parameter but not used yet.
*/
CircleCollider::CircleCollider(GameObject *owner, Vector &offset, float radius,
                               int layer)
    : Collider(owner, layer) {
        // Set the offset of the circle.
        m_offset = offset;
        // Set the radius of the circle.
        m_shape.radius = radius;
        // Set the position of the circle.
        m_shape.x = owner->GetPosition()->m_x + offset.m_x;
        m_shape.y = owner->GetPosition()->m_y + offset.m_y;
}

void CircleCollider::FixedComponentUpdate() {
    // Get the position of the circle.
    m_shape.x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
    m_shape.y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
    // Get the radius of the circle.
    m_shape.radius = GetOwner()->GetWidth() / 2;
}
