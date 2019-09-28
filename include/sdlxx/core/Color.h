/**
 * @file Color.h
 * @author Egor Makarenko
 * @brief Class that describes color
 */

#pragma once

#ifndef SDLXX_CORE_COLOR_H
#define SDLXX_CORE_COLOR_H

#include <cstdint>
#include <string>

namespace sdlxx::core {

class Color {
public:
  /**
   * @brief Construct a black opaque Color
   */
  Color();

  /**
   * @brief Construct an opaque Color based on its hexadecimal value
   *
   * Examples:
   *
   * Color(0xFF00FF) should give you a bright pink
   * Color(0x0000FF) should give you full blue
   * Color(0xC0FFEE) I don't know what it is but it has a nice name
   *
   * @param color_mask hexadecimal value of a color
   */
  Color(uint32_t color_mask);

  /// Creates a RGBA color.
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

  /// Creates a opaque color based on a color name.
  ///
  /// You know, "red", "black", "cyan"...
  Color(std::string& colorName);

  /// Adds the RGB values of two colors.
  ///
  /// @note If the alpha value is different, defaults to opaque.
  /// @note If the value is out of range, it's padded.
  ///
  Color operator+(const Color& color) const;

  /// Subtracts the RGB values of two colors.
  ///
  /// @note If the alpha value is different, defaults to opaque.
  /// @note If the value is out of range, it's padded.
  Color operator-(const Color& color) const;

  /// Tests if two RGBA colors are completely equal.
  bool operator==(const Color& color) const;

  /// Tests if two RGBA colors are different.
  bool operator!=(const Color& color) const;

  const uint8_t red;    ///< Red component (0 is none, 255 is full).
  const uint8_t green;  ///< Green component (0 is none, 255 is full).
  const uint8_t blue;   ///< Blue component  (0 is none, 255 is full).
  const uint8_t alpha;  ///< Alpha component (0 is transparent, 255 is opaque).
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_COLOR_H
