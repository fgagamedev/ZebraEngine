#include "Components/CircleRenderer.hpp"

CircleRenderer::CircleRenderer(GameObject *owner, Vector offset, float radius)
    : Component(owner, C_DRAW) {
    m_offset = offset;
    m_radius = radius;
}

void CircleRenderer::ComponentUpdate() {
    int x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
    int y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
    auto center = Vector(x, y);
    GraphicsSystem::GetInstance()->DrawFillCircle(center, m_radius, m_red,
                                                m_green, m_bluen, m_alpha);
}

void CircleRenderer::SetColor(int red, int green, int blue, int alpha) {
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_alpha = alpha;
}
