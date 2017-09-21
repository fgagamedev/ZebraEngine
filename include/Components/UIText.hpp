/**
    @file UIText.hpp
    @brief This class defines the colors texts and its positions shown in the game.
    @copyright LGPL. MIT License.
*/

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

    // Sets the object offset, of type vector.
    Vector m_offset = Vector(0, 0);

    // Sets the object mode, an unsigned 8-bit integer type.
    Uint8 m_mode = 0;

    // Sets the message of the uitext as a string.
    string m_message;

    // Sets the object's surface as a collection of pixels used in software blitting.
    SDL_Surface *m_surface = nullptr;

    // The internal structure containing font information.
    TTF_Font *m_font = nullptr;

    // Represents colors.
    SDL_Color m_color;
    SDL_Color m_background;

    // An driver-specific representation of pixel data.
    SDL_Texture *m_texture = nullptr;

    // Sets a rectangle with the origin at the upper left.
    SDL_Rect m_rect;

    void OnPropertyChange();
};

#endif
