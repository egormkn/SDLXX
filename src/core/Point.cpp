#include <sdlxx/core/Point.h>

using namespace sdlxx::core;

Point::Point(int x, int y) : x(x), y(y) {}

int Point::getX() const { return x; }

int Point::getY() const { return y; }
