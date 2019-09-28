/**
 * @file Point.h
 * @author Egor Makarenko
 * @brief Describes a 2D point class
 */

#pragma once

#ifndef SDLXX_CORE_POINT_H
#define SDLXX_CORE_POINT_H

namespace sdlxx::core {

/**
 * @brief Describes a 2D point class
 */
class Point {
public:
  Point(int x = 0, int y = 0);

  int getX() const;

  int getY() const;

private:
  int x;
  int y;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_POINT_H
