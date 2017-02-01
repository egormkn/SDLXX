#include "Point.h"

SDLXX::Point::Point(int x, int y) {
    point = new SDL_Point;
    point->x = x;
    point->y = y;
}

SDLXX::Point::~Point() {
    delete point;
}

int SDLXX::Point::getX() {
    return point->x;
}

int SDLXX::Point::getY() {
    return point->y;
}
