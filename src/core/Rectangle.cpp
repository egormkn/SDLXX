#include <SDL_rect.h>
#include <sdlxx/core/Rectangle.h>

using namespace sdlxx::core;

Rectangle::Rectangle(int x, int y, int width, int height) {
  rectangle_ptr = new SDL_Rect{x, y, width, height};
}

Rectangle::~Rectangle() { delete static_cast<SDL_Rect*>(rectangle_ptr); }

int Rectangle::getX() const { return static_cast<SDL_Rect*>(rectangle_ptr)->x; }

int Rectangle::getY() const { return static_cast<SDL_Rect*>(rectangle_ptr)->y; }

int Rectangle::getWidth() const {
  return static_cast<SDL_Rect*>(rectangle_ptr)->w;
}

int Rectangle::getHeight() const {
  return static_cast<SDL_Rect*>(rectangle_ptr)->h;
}
