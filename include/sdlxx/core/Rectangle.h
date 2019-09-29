/**
 * @file Rectangle.h
 * @author Egor Makarenko
 * @brief Class that represents a rectangle with the origin at the upper left
 */

#pragma once

#ifndef SDLXX_CORE_RECTANGLE_H
#define SDLXX_CORE_RECTANGLE_H

#include <SDL_rect.h>

namespace sdlxx::core {

/**
 * @brief Class that represents a rectangle with the origin at the upper left
 */
class Rectangle {
public:
  /**
   * @brief Construct a new rectangle
   *
   * @param x, y Coordinates of the upper left corner
   * @param width, height Dimensions of the rectangle
   */
  Rectangle(int x, int y, int width = 0, int height = 0);

  /**
   * @brief Destroy the rectangle
   */
  ~Rectangle();

  int getX() const;

  int getY() const;

  int getWidth() const;

  int getHeight() const;

  friend class Renderer;

private:
  void* rectangle_ptr = nullptr;
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_RECTANGLE_H
