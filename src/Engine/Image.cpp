/**
    @file Image.cpp
    @brief Manage images used in the game.
    @copyright MIT License.
*/

#include "Engine/Image.hpp"
#include "Engine/SDLSystem.hpp"

#include "Log/log.hpp"

/**
    @brief Simple constructor of the Image class.
*/
Image::Image() {

}

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
void Image::LoadImage(std::string path, int _x, int _y, int _width, int _height) {

    // Responsible for loading the image and checking for errors.
    SDL_Surface *surface = IMG_Load(path.c_str());

    // Checks if the surface exists, if not, return an error message. 
    if (!surface) {
        ERROR(IMG_GetError());
    }

    m_texture = SDL_CreateTextureFromSurface(SDLSystem::GetInstance()
                                             -> GetRenderer(),
                                             surface);

    // Checks if the texture exists, if not, return an error message.                                          
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
    // Checks for the pointer of the image, if not, set it.
    if (!m_sdlPivotPtr) {
        m_sdlPivotPtr = &m_sdlPivot;
    }
    m_sdlPivot.x = _x;
    m_sdlPivot.y = _y;

    // Checks for the pivot pointer of the image, if not, set it.
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

    // Checks the image orientation, if horizontal, sets a flag. 
    if (horizontal) {
        flag = SDL_FLIP_HORIZONTAL;
    }
    
    // Checks the image orientation, if vertical, sets a flag. 
    if (vertical) {
        flag = (SDL_RendererFlip)(flag | SDL_FLIP_VERTICAL);
    }

    m_sdlFlip = flag;
}
