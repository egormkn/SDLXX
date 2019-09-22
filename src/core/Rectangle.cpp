#include <sdlxx/core/Rectangle.h>

SDLXX::Rectangle::Rectangle(int x, int y, int width, int height) {
    rectangle = new SDL_Rect;
    rectangle->x = x;
    rectangle->y = y;
    rectangle->w = width;
    rectangle->h = height;
}

SDLXX::Rectangle::~Rectangle() {
    delete rectangle;
}

SDL_Rect *SDLXX::Rectangle::getSDLRectangle() const {
    return rectangle;
}

int SDLXX::Rectangle::getX() const {
    return rectangle->x;
}

int SDLXX::Rectangle::getY() const {
    return rectangle->y;
}

int SDLXX::Rectangle::getWidth() const {
    return rectangle->w;
}

int SDLXX::Rectangle::getHeight() const {
    return rectangle->h;
}
