#include "Engine/Frame.hpp"

Frame::Frame(int x, int y, int width, int height) {
  srcRect.x = x;
  srcRect.y = y;
  srcRect.w = width;
  srcRect.h = height;
}

SDL_Rect *Frame::GetRect() { return &srcRect; }