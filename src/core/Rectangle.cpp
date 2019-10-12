#include <SDL_rect.h>
#include <sdlxx/core/Rectangle.h>

using namespace sdlxx::core;

Rectangle::Rectangle(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

Point Rectangle::getOrigin() const { return {x, y}; }

Dimensions Rectangle::getDimensions() const { return {width, height}; }
