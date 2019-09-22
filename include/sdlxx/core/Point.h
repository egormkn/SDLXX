#ifndef SDLXX_POINT_H
#define SDLXX_POINT_H

#include <SDL_rect.h>

namespace sdlxx::core {
    class Point {
    public:
        Point(int x = 0, int y = 0);

        ~Point();

        int getX() const;

        int getY() const;

        void setPoint(int x, int y);

        void setX(int x);

        void setY(int y);

        SDL_Point &getSDLPoint();

    private:
        SDL_Point *point = nullptr;
    };

    using Dimensions = Point;
}

#endif // SDLXX_POINT_H
