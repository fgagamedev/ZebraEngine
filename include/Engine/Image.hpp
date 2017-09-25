/**
    @file Image.hpp
    @brief Manage images used in the game.
    @copyright MIT License.
*/

#ifndef __IMAGE__
#define __IMAGE__

#include "Engine/sdl2include.hpp"

#include "Math/Vector.hpp"

#include <string>

class Image {
public:
    // Save image height and width.
    int width;
    int height;

    // They represent the X and Y axes for the image vector.
    int x;
    int y;

    // Constructors
    Image();
    Image(std::string path, int _x, int _y, int _width, int _height);

    // method for loading the image
    void LoadImage(std::string path, int _x, int _y, int width, int height);

    // getters and setters
    SDL_Texture *GetTexture();
    SDL_Rect *GetRect();

    inline double GetRotationAngle() {
        return m_rotation;
    };
    inline SDL_Point *GetSDLPivot() {
        return m_sdlPivotPtr;
    };
    inline Vector *GetPivot() {
        return m_pivot;
    };
    inline SDL_RendererFlip GetSDLFlip() {
        return m_sdlFlip;
    };
    inline void Rotate(double angles) {
        m_rotation = angles;
    };
    void SetPivot(int _x, int _y);
    void Flip(bool horizontal, bool vertical);

private:

    // Simple direct media layer variable for handling texture image.
    SDL_Texture *m_texture = nullptr;

    // Simple direct media layer variable for handling rectangle image.
    SDL_Rect m_rectangle;

    // Sets the angle of image rotation.
    double m_rotation = 0;

    // Simple direct media layer variable for pivot.
    SDL_Point m_sdlPivot;

    // Simple direct media layer pointer for pivot, initialize of nullptr.
    SDL_Point *m_sdlPivotPtr = nullptr;

    // Simple direct media layer for flip of image.
    SDL_RendererFlip m_sdlFlip = (SDL_RendererFlip)0;

    // adpted image properties
    Vector *m_pivot = nullptr;

    // Sets whether there will be horizontal flip.
    bool m_horizontalFlip = false;

    // Sets whether there will be vertical flip.
    bool m_verticalFlip = false;
};

#endif
