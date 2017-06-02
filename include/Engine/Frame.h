#ifndef __FRAME__
#define __FRAME__

#include "Engine/sdl2include.h"

class Frame {
public:
  Frame(int x, int y, int width, int height);
  SDL_Rect *GetRect();

private:
  SDL_Rect srcRect;
};

#endif // __FRAME__