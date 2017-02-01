#ifndef SDLXX_OBJECT_H
#define SDLXX_OBJECT_H

#include "../base/Point.h"

namespace SDLXX {
    class Object {
        Object(int x, int y, int w, int h, double m = 0.0, double a = 0.0) {
            position = new Point(x, y);
            position = new Point(x, y);
        }

    private:
        double mass = 0.0;
        double acceleration = 0.0;
        Point *position = nullptr, *rotation = nullptr;
    };
}

#endif // SDLXX_OBJECT_H
