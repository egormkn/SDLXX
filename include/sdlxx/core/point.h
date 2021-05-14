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
 * \file point.h
 *
 * \brief A structure that represents a 2D point.
 */

#pragma once

#ifndef SDLXX_CORE_POINT_H
#define SDLXX_CORE_POINT_H

namespace sdlxx::core {

/**
 * \brief A structure that represents a 2D point.
 */
struct Point {
  int x;  ///< X coordinate value
  int y;  ///< Y coordinate value

  /**
   * \brief Construct a new point at (0, 0).
   */
  Point();

  /**
   * \brief Construct a new point with given coordinates.
   *
   * \param x, y Coordinates of a point
   */
  Point(int x, int y);
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_POINT_H
