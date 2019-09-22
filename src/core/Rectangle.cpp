#include <sdlxx/core/Rectangle.h>

sdlxx::core::Rectangle::Rectangle(int x, int y, int width, int height) {
    rectangle = new SDL_Rect;
    rectangle->x = x;
    rectangle->y = y;
    rectangle->w = width;
    rectangle->h = height;
}

sdlxx::core::Rectangle::~Rectangle() {
    delete rectangle;
}

SDL_Rect *sdlxx::core::Rectangle::getSDLRectangle() const {
    return rectangle;
}

int sdlxx::core::Rectangle::getX() const {
    return rectangle->x;
}

int sdlxx::core::Rectangle::getY() const {
    return rectangle->y;
}

int sdlxx::core::Rectangle::getWidth() const {
    return rectangle->w;
}

int sdlxx::core::Rectangle::getHeight() const {
    return rectangle->h;
}
