/**
 * @file Point.h
 * @author Egor Makarenko
 * @brief Class that represents a 2D point
 */

#pragma once

#ifndef SDLXX_CORE_POINT_H
#define SDLXX_CORE_POINT_H

namespace sdlxx::core {

/**
 * @brief Class that represents a 2D point
 */
class Point {
public:
  /**
   * @brief Construct a new point with given coordinates
   *
   * @param x, y Coordinates of a point
   */
  Point(int x = 0, int y = 0);

  /// X coordinate value
  int x;

  /// Y coordinate value
  int y;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_POINT_H
