/**
 * @file Rectangle.h
 * @author Egor Makarenko
 * @brief Class that represents a rectangle
 */

#pragma once

#ifndef SDLXX_CORE_RECTANGLE_H
#define SDLXX_CORE_RECTANGLE_H

#include <SDL_rect.h>

namespace sdlxx::core {

/**
 * @brief A rectangle, with the origin at the upper left
 */
class Rectangle {
public:
  Rectangle(int x, int y, int width = 0, int height = 0);

  ~Rectangle();

  SDL_Rect* getSDLRectangle() const;

  int getX() const;

  int getY() const;

  int getWidth() const;

  int getHeight() const;

private:
  SDL_Rect* rectangle = nullptr;
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_RECTANGLE_H
