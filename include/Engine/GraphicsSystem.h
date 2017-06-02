#ifndef __GRAPHICS_SYSTEM__
#define __GRAPHICS_SYSTEM__

#include "Engine/Frame.h"
#include "Engine/Image.h"
#include "Math/Vector.h"

#include <math.h>

class Image;

class GraphicsSystem {
public:
  // singleton getter
  static GraphicsSystem *GetInstance();
  // draw to renderer function
  void Draw(Image *img, Vector *position, std::pair<int, int> sizes);
  void DrawFrame(Image *img, Frame *frame, Vector *position);
  void DrawText(SDL_Texture *texture, SDL_Rect *destRect);
  void DrawPoint(Vector point);
  void DrawCircle(Vector &center, float radius, Uint8 r, Uint8 g, Uint8 b,
                  Uint8 a);
  void DrawFillCircle(Vector &center, float radius, Uint8 r, Uint8 g, Uint8 b,
                      Uint8 a);
  void DrawFillRectangle(Vector &position, int width, int height, Uint8 r,
                         Uint8 g, Uint8 b, Uint8 a);

private:
  // singleton instance
  static GraphicsSystem *m_instance;

  // constructor and destructor
  GraphicsSystem();
  ~GraphicsSystem();
};

#endif // __GRAPHICS_SYSTEM__
