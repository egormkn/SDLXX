#include <sdlxx/core/Point.h>

sdlxx::core::Point::Point(int x, int y) {
    point = new SDL_Point;
    point->x = x;
    point->y = y;
}

sdlxx::core::Point::~Point() {
    delete point;
}

int sdlxx::core::Point::getX() const {
    return point->x;
}

int sdlxx::core::Point::getY() const {
    return point->y;
}

void sdlxx::core::Point::setPoint(int x, int y) {
    point->x = x;
    point->y = y;
}

void sdlxx::core::Point::setX(int x) {
    point->x = x;
}

void sdlxx::core::Point::setY(int y) {
    point->y = y;
}

SDL_Point &sdlxx::core::Point::getSDLPoint() {
    return *point;
}
