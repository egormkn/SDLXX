/**
 * @file Font.h
 * @author Egor Makarenko
 * @brief Class that represents the TrueType font
 */

#pragma once

#ifndef SDLXX_TTF_FONT_H
#define SDLXX_TTF_FONT_H

#include <string>

#include <sdlxx/core/Color.h>
#include <sdlxx/core/Surface.h>

namespace sdlxx::ttf {

/**
 * @brief Class that represents the TrueType font
 */
class Font {
public:
  enum { TTF_MODE_SOLID, TTF_MODE_SHADED, TTF_MODE_BLENDED };

  /**
   * @brief Open a font file and create a Font of the specified point size.
   *
   * Some .fon fonts will have several sizes embedded in the file, so the
   * point size becomes the index of choosing which size to load. If the value
   * is too high, the last indexed size will be the default.
   *
   * @param file Path to the *.ttf or *.fon file
   * @param point_size Point size (based on 72 DPI) to load
   * @param index Index of font face from a file containing multiple font faces
   */
  Font(const std::string& file, int point_size, int index = 0);

  ~Font();

  sdlxx::core::Surface render(
      const std::string& text, int mode, const sdlxx::core::Color& color,
      const sdlxx::core::Color& bg = sdlxx::core::Color(0x00000000)) const;

  sdlxx::core::Surface render(
      wchar_t ch, int mode, const sdlxx::core::Color& color,
      const sdlxx::core::Color& bg = sdlxx::core::Color(0x00000000)) const;

  // TODO: Open font by file descriptor

  // TODO: Get font properties

private:
  void* font_ptr = nullptr;

  Font(void* font_ptr);
};
}  // namespace sdlxx::ttf

#endif  // SDLXX_TTF_FONT_H
