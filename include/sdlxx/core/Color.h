/**
 * @file Color.h
 * @author Egor Makarenko
 * @brief Class that represents a color
 */

#pragma once

#ifndef SDLXX_CORE_COLOR_H
#define SDLXX_CORE_COLOR_H

#include <cstdint>
#include <string>

namespace sdlxx::core {

/**
 * @brief Class that represents a color
 */
class Color {
public:
  /**
   * @brief Construct a black opaque color
   */
  Color();

  /**
   * @brief Construct a color from its hexadecimal ARGB value
   *
   * Examples:
   *
   * Color(0xFF00FF) should give you a bright pink
   * Color(0x0000FF) should give you full blue
   * Color(0xC0FFEE) I don't know what it is but it has a nice name
   *
   * @param color hexadecimal value of a color
   */
  Color(uint32_t color);

  /**
   * @brief Construct a color from its RGBA values
   *
   * @param r Red component
   * @param g Green component
   * @param b Blue component
   * @param a Alpha component
   */
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

  // TODO: Add operators

  const uint8_t red;    ///< Red component (0 is none, 255 is full)
  const uint8_t green;  ///< Green component (0 is none, 255 is full)
  const uint8_t blue;   ///< Blue component  (0 is none, 255 is full)
  const uint8_t alpha;  ///< Alpha component (0 is transparent, 255 is opaque)
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_COLOR_H
