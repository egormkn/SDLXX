/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)

  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the Dimensions structure that represents the dimensions of a 2D object.
 */

#ifndef SDLXX_CORE_DIMENSIONS_H
#define SDLXX_CORE_DIMENSIONS_H

namespace sdlxx {

/**
 * \brief A structure that represents the dimensions of a 2D object.
 */
struct Dimensions {
  int width = 0;   ///< Width of a 2D object
  int height = 0;  ///< Height of a 2D object

  /**
   * \brief Construct a new dimensions object with width = height = 0.
   */
  constexpr Dimensions() = default;

  /**
   * \brief Construct a new dimensions object with given width and height.
   *
   * \param width Width of a 2D object.
   * \param height Height of a 2D object.
   */
  constexpr Dimensions(int width, int height) : width(width), height(height) {}
};

}  // namespace sdlxx

#endif  // SDLXX_CORE_DIMENSIONS_H
