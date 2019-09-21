#include "Point.h"

SDLXX::Point::Point(int x, int y) {
    point = new SDL_Point;
    point->x = x;
    point->y = y;
}

SDLXX::Point::~Point() {
    delete point;
}

int SDLXX::Point::getX() const {
    return point->x;
}

int SDLXX::Point::getY() const {
    return point->y;
}

void SDLXX::Point::setPoint(int x, int y) {
    point->x = x;
    point->y = y;
}

void SDLXX::Point::setX(int x) {
    point->x = x;
}

void SDLXX::Point::setY(int y) {
    point->y = y;
}

SDL_Point &SDLXX::Point::getSDLPoint() {
    return *point;
}
