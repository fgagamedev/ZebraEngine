/**
    @file Frame.hpp
    @brief Manages the frame of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __FRAME__
#define __FRAME__

#include "Engine/sdl2include.hpp"

class Frame {
public:
    Frame(int x, int y, int width, int height);
    SDL_Rect *GetRect();

private:
    // Rectangular area of the frame
    SDL_Rect srcRect;
};

#endif // __FRAME__
