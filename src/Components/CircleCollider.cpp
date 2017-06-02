#include "Components/CircleCollider.h"

CircleCollider::CircleCollider(GameObject *owner, Vector &offset, float radius,
                               int layer)
    : Collider(owner, layer) {
  m_offset = offset;
  m_shape.radius = radius;
  m_shape.x = owner->GetPosition()->m_x + offset.m_x;
  m_shape.y = owner->GetPosition()->m_y + offset.m_y;
}

void CircleCollider::FixedComponentUpdate() {
  m_shape.x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
  m_shape.y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
}
