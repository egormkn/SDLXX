#ifndef SDLXX_RECTANGLE_H
#define SDLXX_RECTANGLE_H

#include <SDL_rect.h>

namespace SDLXX {
    class Rectangle {
    public:
        Rectangle(int x, int y, int width = 0, int height = 0) {
            rectangle = new SDL_Rect;
            rectangle->x = x;
            rectangle->y = y;
            rectangle->w = width;
            rectangle->h = height;
        }

        ~Rectangle() {
            delete rectangle;
        }

        SDL_Rect &getSDLRectangle() {
            return *rectangle;
        }

    private:
        SDL_Rect *rectangle;
    };
}

#endif // SDLXX_RECTANGLE_H
