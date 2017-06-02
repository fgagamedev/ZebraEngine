#include "Components/UIText.h"

UIText::UIText(GameObject *owner, string message, string fontPath, int size,
               Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 mode)
    : Component(owner, C_DRAW) {
  m_message = message;

  m_rect.x = owner->GetPosition()->m_x;
  m_rect.y = owner->GetPosition()->m_y;
  m_rect.w = owner->GetWidth();
  m_rect.h = owner->GetHeight();

  m_font = TTF_OpenFont(fontPath.c_str(), size);
  if (!m_font)
    SDL_TTF_ERROR("Font could not be loaded");
  m_color = {r, g, b, a};

  m_background = {0, 0, 0, 0};

  m_mode = mode;

  OnPropertyChange();
}

void UIText::Start() {}

void UIText::SetOffset(Vector &offset) { m_offset = offset; }

void UIText::ComponentUpdate() {
  m_rect.x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
  m_rect.y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
  m_rect.w = GetOwner()->GetWidth();
  m_rect.h = GetOwner()->GetHeight();

  GraphicsSystem::GetInstance()->DrawText(m_texture, &m_rect);
}

void UIText::FixedComponentUpdate() {}

void UIText::OnPropertyChange() {
  m_surface = nullptr;

  switch (m_mode) {
  case 0:
    m_surface = TTF_RenderText_Solid(m_font, m_message.c_str(), m_color);
    break;
  case 1:
    m_surface = TTF_RenderText_Blended(m_font, m_message.c_str(), m_color);
    break;
  case 2:
    m_surface =
        TTF_RenderText_Shaded(m_font, m_message.c_str(), m_color, m_background);
  }

  m_texture = SDL_CreateTextureFromSurface(
      SDLSystem::GetInstance()->GetRenderer(), m_surface);

  SDL_FreeSurface(m_surface);
}

void UIText::SetText(string text) {
  m_message = text;
  OnPropertyChange();
}
