#include "Components/RectangleCollider.hpp"

/**
    @file RectangleCollider.cpp
    @brief Methods that manages all game's collisions.
    @copyright LGPL MIT License.
*/


/**
    @brief Initializes RectangleCollider instance.
    @param[in] GameObject *owner - owns the component.
    @param[in] offset - the position of x and y components.
    @param[in] width - the width of Gameobject.
    @param[in] height - the height of Gameobject.
    @param[in] layer - the Uint8 m_layer of Gameobject
*/
RectangleCollider::RectangleCollider(GameObject *owner, Vector offset,
                                     float width, float height,
                                     int layer)
    : Collider(owner, layer) {
    m_owner = owner;
    m_offset = offset;
    m_shape.width = width;
    m_shape.height = height;
    m_shape.x = owner->GetPosition()->m_x + offset.m_x;
    m_shape.y = owner->GetPosition()->m_y + offset.m_y;
}

/**
    @brief Updates the position x, y, height and width of a component.
*/
void RectangleCollider::FixedComponentUpdate() {
    // sets the position and the shape of the rectangle
    m_shape.x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
    m_shape.y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
    m_shape.width = GetOwner()->GetWidth();
    m_shape.height = GetOwner()->GetHeight();
}
