#include "Components/RectangleRenderer.hpp"

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
    GraphicsSystem::GetInstance()->DrawFillRectangle(pos, m_width, m_height,
                                                   m_red, m_green, m_blue,
                                                   m_alpha);
}

void RectangleRenderer::SetColor(int red, int green, int blue, int alpha) {
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_alpha = alpha;
}
