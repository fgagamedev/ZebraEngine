/**
    @file Frame.cpp
    @brief Manages the frame of the game.
    @copyright LGPL. MIT License.
*/

#include "Engine/Frame.hpp"

/**
    @brief Set start coordinates and frame size.
    @param[in] x - Horizontal coordinate of the frame.
    @param[in] y - Vertical coordinate of the frame.
    @param[in] width - Horizontal frame size
    @param[in] height - Vertical frame size.
*/
Frame::Frame(int x, int y, int width, int height) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = width;
    srcRect.h = height;
}

/**
    @brief Get informations about the frame.
    @return - The rectangular area of the frame
*/
SDL_Rect *Frame::GetRect() {
    return &srcRect;
}
