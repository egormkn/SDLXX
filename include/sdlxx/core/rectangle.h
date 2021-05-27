/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the Rectangle structure that represents a 2D rectangle.
 */

#pragma once

#ifndef SDLXX_CORE_RECTANGLE_H
#define SDLXX_CORE_RECTANGLE_H

#include "sdlxx/core/dimensions.h"
#include "sdlxx/core/point.h"

namespace sdlxx::core {

/**
 * \brief A structure that represents a 2D rectangle with the origin at the upper left corner.
 *
 * \upstream SDL_Rect
 */
struct Rectangle {
  int x;       ///< X coordinate of the upper left corner
  int y;       ///< Y coordinate of the upper left corner
  int width;   ///< Width of the rectangle
  int height;  ///< Height of the rectangle

  /**
   * \brief Construct a new rectangle of given size at the given point.
   *
   * \param x, y Coordinates of the upper left corner.
   * \param width, height Dimensions of the rectangle.
   */
  Rectangle(int x, int y, int width, int height);

  /**
   * \brief Construct a new rectangle of given size at the given point.
   *
   * \param origin Coordinates of the upper left corner.
   * \param dimensions Dimensions of the rectangle.
   */
  Rectangle(Point origin, Dimensions dimensions);

  /**
   * \brief Get the upper left corner.
   *
   * \return Point The upper left corner of a rectangle.
   */
  Point getOrigin() const;

  /**
   * \brief Get the dimensions of a rectangle.
   *
   * \return Dimensions The dimensions of a rectangle.
   */
  Dimensions getDimensions() const;
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_RECTANGLE_H
