#ifndef SDLXX_POINT_H
#define SDLXX_POINT_H

#include <SDL_rect.h>

namespace SDLXX {
    class Point {
    public:
        Point(int x, int y);

        ~Point();

        int getX();

        int getY();

    private:
        SDL_Point *point;
    };
}

#endif //SDLXX_POINT_H
