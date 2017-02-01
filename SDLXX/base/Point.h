#ifndef SDLXX_POINT_H
#define SDLXX_POINT_H

#include <SDL_rect.h>

namespace SDLXX {
    class Point {
    public:
        Point(int x, int y) {
            point = new SDL_Point;
            point->x = x;
            point->y = y;
        }

        ~Point() {
            delete point;
        }

        int getX() const {
            return point->x;
        }

        int getY() const {
            return point->y;
        }

        SDL_Point &getSDLPoint() {
            return *point;
        }

    private:
        SDL_Point *point = nullptr;
    };
}

#endif // SDLXX_POINT_H
