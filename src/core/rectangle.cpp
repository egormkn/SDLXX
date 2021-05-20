#include "sdlxx/core/rectangle.h"

using namespace sdlxx::core;

Rectangle::Rectangle(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

Rectangle::Rectangle(Point origin, Dimensions dimensions)
    : x(origin.x), y(origin.y), width(dimensions.width), height(dimensions.height) {}

Point Rectangle::getOrigin() const { return {x, y}; }

Dimensions Rectangle::getDimensions() const { return {width, height}; }
