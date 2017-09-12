#include "Engine/Image.hpp"
#include "Engine/SDLSystem.hpp"

#include "Log/log.hpp"

/**
    @file Image.cpp
    @brief Manage images used in the game.
    @copyright MIT License.
*/

/**
    @brief Simple constructor of the Image class.
*/
Image::Image() {}

/**
    @brief Constructor of the Image class that loads the image.
    @param[in] path
    @param[in] _x Horizontal coordinate of the image.
    @param[in] _y Vertical coordinate of the image.
    @param[in] _width Vertical size of the image.
    @param[in] _height Horizontal size of the image.
*/
Image::Image(std::string path, int _x, int _y, int _width, int _height) {
    LoadImage(path, _x, _y, _width, _height);
}

/**
@brief Load a image in the game.
    @param[in] path
    @param[in] _x Horizontal coordinate of the image.
    @param[in] _y Vertical coordinate of the image.
    @param[in] _width Vertical size of the image.
    @param[in] _height Horizontal size of the image.
*/
void Image::LoadImage(std::string path, int _x, int _y, int _width,
                      int _height) {
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface) {
        ERROR(IMG_GetError());
    }

    m_texture = SDL_CreateTextureFromSurface(
                                        SDLSystem::GetInstance()->GetRenderer(),
                                        surface);

    if (!m_texture) {
        ERROR(SDL_GetError());
    }

    SDL_FreeSurface(surface);

    m_rectangle.x = _x;
    m_rectangle.y = _y;
    m_rectangle.w = _width;
    m_rectangle.h = _height;

    width = _width;
    height = _height;
}

/**
    #brief Getter for m_texture.
*/
SDL_Texture *Image::GetTexture() {
    return m_texture;
}

/**
    @brief Getter for m_rectangle.
*/
SDL_Rect *Image::GetRect() {
    return &m_rectangle;
}

void Image::SetPivot(int _x, int _y) {
    if (!sdlPivotPtr) {
        sdlPivotPtr = &sdlPivot;
    }
    sdlPivot.x = _x;
    sdlPivot.y = _y;

    if (!m_pivot) {
        m_pivot = new Vector(0, 0);
    }
    m_pivot->m_x = _x;
    m_pivot->m_y = _y;
}

/**
    @brief Flip a image horizontally and/or vertically
    @param[in] horizontal Inform if the image must be flipped horizontally.
    @param[in] vertical Inform if the image must be flipped vertically.
*/
void Image::Flip(bool horizontal, bool vertical) {
    m_horizontalFlip = horizontal;
    m_verticalFlip = vertical;

    SDL_RendererFlip flag = SDL_FLIP_NONE;
    if (horizontal) {
        flag = SDL_FLIP_HORIZONTAL;
    }
    if (vertical) {
        flag = (SDL_RendererFlip)(flag | SDL_FLIP_VERTICAL);
    }

    sdlFlip = flag;
}
