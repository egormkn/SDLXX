/**
 * @file Rectangle.h
 * @author Egor Makarenko
 * @brief Class that represents a rectangle with the origin at the upper left
 */

#pragma once

#ifndef SDLXX_CORE_RECTANGLE_H
#define SDLXX_CORE_RECTANGLE_H

#include <sdlxx/core/Point.h>
#include <sdlxx/core/Dimensions.h>

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
   * @brief Get the upper left corner
   *
   * @return Point The upper left corner of a rectangle
   */
  Point getOrigin() const;

  /**
   * @brief Get the dimensions of a rectangle
   *
   * @return Dimensions The dimensions of a rectangle
   */
  Dimensions getDimensions() const;

  /// Coordinates of the upper left corner
  int x, y;

  /// Dimensions of the rectangle
  int width, height;
};
}  // namespace sdlxx::core

#endif  // SDLXX_CORE_RECTANGLE_H
