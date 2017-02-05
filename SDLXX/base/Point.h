#ifndef SDLXX_POINT_H
#define SDLXX_POINT_H

#include <SDL_rect.h>

namespace SDLXX {
    class Point {
    public:
        Point(int x = 0, int y = 0) {
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

        void setPoint(int x, int y) {
            point->x = x;
            point->y = y;
        }

        void setX(int x) {
            point->x = x;
        }

        void setY(int y) {
            point->y = y;
        }

        SDL_Point &getSDLPoint() {
            return *point;
        }

    private:
        SDL_Point *point = nullptr;
    };

    using Dimensions = Point;
}

#endif // SDLXX_POINT_H
