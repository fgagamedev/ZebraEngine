#include "Components/RectangleCollider.h"

RectangleCollider::RectangleCollider(GameObject *owner, Vector offset,
                                     float width, float height, int layer)
    : Collider(owner, layer) {
  m_offset = offset;
  m_shape.width = width;
  m_shape.height = height;
  m_shape.x = owner->GetPosition()->m_x + offset.m_x;
  m_shape.y = owner->GetPosition()->m_y + offset.m_y;
}

void RectangleCollider::FixedComponentUpdate() {
  m_shape.x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
  m_shape.y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
}
