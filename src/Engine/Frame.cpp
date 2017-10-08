/**
    @file Frame.cpp
    @brief Manages the frame of the game.
    @copyright LGPL. MIT License.
*/

#include "Engine/Frame.hpp"

/**
    @brief Set start coordinates and frame size.
    @param[in] positionX - Horizontal coordinate of the frame.
    @param[in] positionY - Vertical coordinate of the frame.
    @param[in] width - Horizontal frame size
    @param[in] height - Vertical frame size.
*/
Frame::Frame(int positionX, int positionY, int width, int height) {
    sourceRectangle.x = positionX;
    sourceRectangle.y = positionY;
    sourceRectangle.w = width;
    sourceRectangle.h = height;
}

/**
    @brief Get informations about the frame.
    @return - The rectangular area of the frame
*/
SDL_Rect *Frame::GetRect() {
    return &sourceRectangle;
}
