#include "Components/RectangleRenderer.h"

RectangleRenderer::RectangleRenderer(GameObject *owner, Vector offset,
                                     int width, int height)
    : Component(owner, C_DRAW) {
  m_offset = offset;
  m_width = width;
  m_height = height;
}

void RectangleRenderer::ComponentUpdate() {
  int x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
  int y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
  auto pos = Vector(x, y);
  GraphicsSystem::GetInstance()->DrawFillRectangle(pos, m_width, m_height, m_r,
                                                   m_g, m_b, m_a);
}

void RectangleRenderer::SetColor(int r, int g, int b, int a) {
  m_r = r;
  m_g = g;
  m_b = b;
  m_a = a;
}
