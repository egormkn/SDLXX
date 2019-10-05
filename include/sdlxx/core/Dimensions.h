/**
 * @file Point.h
 * @author Egor Makarenko
 * @brief Class that represents the dimensions of a 2D object
 */

#pragma once

#ifndef SDLXX_CORE_DIMENSIONS_H
#define SDLXX_CORE_DIMENSIONS_H

namespace sdlxx::core {

/**
 * @brief Class that represents the dimensions of a 2D object
 */
class Dimensions {
public:
  /**
   * @brief Construct a new dimensions with given width and height
   *
   * @param width Width of a 2D object
   * @param height Height of a 2D object
   */
  Dimensions(unsigned width, unsigned height);

  /// Width of a 2D object
  unsigned width;

  /// Height of a 2D object
  unsigned height;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_DIMENSIONS_H
