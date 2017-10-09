/**
    @file GraphicsSystem.hpp
    @brief Manage the draw of texts and diferent types of images in the game.
    @copyright MIT License.
*/

#ifndef __GRAPHICS_SYSTEM__
#define __GRAPHICS_SYSTEM__

#include "Engine/Frame.hpp"
#include "Engine/Image.hpp"

#include "Math/Vector.hpp"

#include <math.h>

class Image;

class GraphicsSystem {
    public:
        // singleton getter
        static GraphicsSystem *GetInstance();
        // draw to renderer function
        void Draw(Image *img, Vector *position, std::pair<int, int> sizes);
        void DrawFrame(Image *img, Frame *frame, Vector *position,int destw,
                       int desth);
        void DrawText(SDL_Texture *texture, SDL_Rect *destRect);
        void DrawPoint(Vector point);
        void DrawCircle(Vector &center, float radius, Uint8 r, Uint8 g, Uint8 b,
                        Uint8 a);
        void DrawFillCircle(Vector &center, float radius, Uint8 r, Uint8 g,
                            Uint8 b, Uint8 a);
        void DrawFillRectangle(Vector &position, int width, int height, Uint8 r,
                               Uint8 g, Uint8 b, Uint8 a);
        void DrawFillRectangle(SDL_Rect * source, int width, int height,
                               Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    private:
        // Singleton instance.
        static GraphicsSystem *m_instance;

        // constructor and destructor
        GraphicsSystem();
        ~GraphicsSystem();

        const int noErrorReturnValue = 0;
};

#endif // __GRAPHICS_SYSTEM__
