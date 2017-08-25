#ifndef __UI_TEXT__
#define __UI_TEXT__


#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"
#include "Engine/SDLSystem.hpp"
#include "Engine/sdl2include.hpp"

#include "Log/sdl_log.hpp"

#include <string>

using namespace std;

class UIText : public Component {
public:
  UIText(GameObject *owner, string message, string fontPath, int size, Uint8 r,
         Uint8 g, Uint8 b, Uint8 a, Uint8 mode);
  string GetComponentName() override { return "UIText"; };
  void Start() override;
  void FixedComponentUpdate() override;
  void ComponentUpdate() override;
  void SetText(string text);
  void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void SetOffset(Vector &offset);

private:
  Vector m_offset = Vector(0, 0);
  Uint8 m_mode = 0;
  string m_message;
  SDL_Surface *m_surface = nullptr;
  TTF_Font *m_font = nullptr;
  SDL_Color m_color;
  SDL_Color m_background;
  SDL_Texture *m_texture = nullptr;
  SDL_Rect m_rect;

  void OnPropertyChange();
};

#endif
