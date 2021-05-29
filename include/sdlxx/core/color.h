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
 * \brief Header for the Color structure that represents a color.
 */

#pragma once

#ifndef SDLXX_CORE_COLOR_H
#define SDLXX_CORE_COLOR_H

#include <cstdint>

namespace sdlxx::core {

/**
 * \brief A structure that represents a color.
 *
 * \upstream SDL_Color
 */
struct Color {
  uint8_t r;  ///< Red component (0 is none, 255 is full).
  uint8_t g;  ///< Green component (0 is none, 255 is full).
  uint8_t b;  ///< Blue component (0 is none, 255 is full).
  uint8_t a;  ///< Alpha component (0 is transparent, 255 is opaque).

  /**
   * \brief Construct a color from its hexadecimal RGB value.
   *
   * Examples:
   *   Color(0xFF00FF) should give you bright pink
   *   Color(0x0000FF) should give you full blue
   *   Color(0xC0FFEE) I don't know what it is but it has a nice name
   *
   * \param rgb Hexadecimal RGB value of a color.
   */
  Color(uint32_t rgb = 0x000000); // NOLINT

  /**
   * \brief Construct a color from its RGBA values.
   *
   * \param r Red component (0 is none, 255 is full).
   * \param g Green component (0 is none, 255 is full).
   * \param b Blue component (0 is none, 255 is full).
   * \param a Alpha component (0 is transparent, 255 is opaque).
   */
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

  // Predefined colors
  static const Color BLACK;        ///< Black color
  static const Color RED;          ///< Red color
  static const Color GREEN;        ///< Green color
  static const Color YELLOW;       ///< Yellow color
  static const Color BLUE;         ///< Blue color
  static const Color MAGENTA;      ///< Magenta color
  static const Color CYAN;         ///< Cyan color
  static const Color WHITE;        ///< White color
  static const Color TRANSPARENT;  ///< White color
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_COLOR_H
