#ifndef SDLXX_RECTANGLE_H
#define SDLXX_RECTANGLE_H

#include <SDL_rect.h>

namespace SDLXX {
    class Rectangle {
    public:
        Rectangle(int x, int y, int width = 0, int height = 0);

        ~Rectangle();

        SDL_Rect *getSDLRectangle() const;

        int getX() const;

        int getY() const;

        int getWidth() const;

        int getHeight() const;

    private:
        SDL_Rect *rectangle = nullptr;
    };
}

#endif // SDLXX_RECTANGLE_H
