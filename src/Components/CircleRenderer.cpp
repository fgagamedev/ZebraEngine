#include "Components/CircleRenderer.h"

CircleRenderer::CircleRenderer(GameObject *owner, Vector offset, float radius)
    : Component(owner, C_DRAW) {
  m_offset = offset;
  m_radius = radius;
}

void CircleRenderer::ComponentUpdate() {
  int x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
  int y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
  auto center = Vector(x, y);
  GraphicsSystem::GetInstance()->DrawFillCircle(center, m_radius, m_r, m_g, m_b,
                                                m_a);
}

void CircleRenderer::SetColor(int r, int g, int b, int a) {
  m_r = r;
  m_g = g;
  m_b = b;
  m_a = a;
}
