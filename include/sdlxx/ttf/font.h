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
 * \brief Header for the Font class that represents a TrueType font.
 */

#ifndef SDLXX_TTF_FONT_H
#define SDLXX_TTF_FONT_H

#include <cstdint>
#include <memory>
#include <string>

#include "sdlxx/core/exception.h"
#include "sdlxx/core/surface.h"
#include "sdlxx/core/utils/bitmask.h"

// Declaration of the underlying type
using TTF_Font = struct _TTF_Font;  // NOLINT

namespace sdlxx {

struct Color;

/**
 * \brief A class for Surface-related exceptions.
 */
class FontException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a TrueType font.
 *
 * \upstream TTF_Font
 */
class Font {
public:
  /**
   * \brief Enumeration of the font styles
   *
   * \upstream TTF_STYLE_NORMAL
   * \upstream TTF_STYLE_BOLD
   * \upstream TTF_STYLE_ITALIC
   * \upstream TTF_STYLE_UNDERLINE
   * \upstream TTF_STYLE_STRIKETHROUGH
   */
  enum class Style {
    NORMAL = 0x00,
    BOLD = 0x01,
    ITALIC = 0x02,
    UNDERLINE = 0x04,
    STRIKETHROUGH = 0x08
  };

  /**
   * \brief Enumeration of the FreeType hinter settings
   *
   * \upstream TTF_HINTING_NORMAL
   * \upstream TTF_HINTING_LIGHT
   * \upstream TTF_HINTING_MONO
   * \upstream TTF_HINTING_NONE
   */
  enum class Hinting { NORMAL = 0, LIGHT = 1, MONO = 2, NONE = 3 };

  /**
   * \brief Create a non-initialized font.
   */
  Font() = default;

  /**
   * \brief Create a font from the raw pointer to TTF_Font.
   *
   * \param ptr The raw pointer to TTF_Font.
   *
   * \throw FontException if pointer is null.
   */
  explicit Font(TTF_Font* ptr);

  /**
   * \brief Open a font file and create a font of the specified point size.
   *
   * Some .fon fonts will have several sizes embedded in the file, so the point size becomes the
   * index of choosing which size to load. If the value is too high, the last indexed size will be
   * the default.
   *
   * \param path       Path to the *.ttf or *.fon file.
   * \param point_size Point size (based on 72 DPI) to load font as.
   *                   This basically translates to pixel height.
   * \param index      Index of font face from a file containing multiple font faces.
   *
   * \throw FontException on error.
   *
   * \upstream TTF_OpenFont
   * \upstream TTF_OpenFontIndex
   */
  Font(const std::string& path, int point_size, int index = 0);

  // TODO: TTF_OpenFontRW, TTF_OpenFontIndexRW

  /**
   * \brief Get the rendering style of the font as a bitmask of Font::Style values.
   *
   * \return The rendering style of the font as a bitmask of Font::Style values.
   *
   * \upstream TTF_GetFontStyle
   */
  BitMask<Style> GetStyle() const;

  /**
   * \brief Set the rendering style of the font as a bitmask of Font::Style values.
   *
   * \param style The new rendering style of the font as a bitmask of Font::Style values.
   *
   * \upstream TTF_SetFontStyle
   */
  void SetStyle(BitMask<Style> style);

  /**
   * \brief Get the outline size of the font.
   *
   * \return The outline size of the font.
   *
   * \upstream TTF_GetFontOutline
   */
  int GetOutline() const;

  /**
   * \brief Set the outline size of the font.
   *
   * \param outline The new outline size of the font.
   *
   * \upstream TTF_SetFontOutline
   */
  void SetOutline(int outline);

  /**
   * \brief Get the font hinting.
   *
   * \return The hinting of the font.
   *
   * \upstream TTF_GetFontHinting
   */
  Hinting GetHinting() const;

  /**
   * \brief Set the font hinting.
   *
   * \param hinting The hinting of the font.
   *
   * \upstream TTF_SetFontHinting
   */
  void SetHinting(Hinting hinting);

  // TODO: TTF_FontHeight, TTF_FontAscent, TTF_FontDescent, TTF_FontLineSkip, TTF_GetFontKerning,
  // TTF_SetFontKerning, TTF_FontFaces, TTF_FontFaceIsFixedWidth, TTF_FontFaceFamilyName,
  // TTF_FontFaceStyleName, TTF_GlyphIsProvided, TTF_GlyphMetrics, TTF_SizeText, TTF_SizeUTF8,
  // TTF_SizeUNICODE, TTF_GetFontKerningSizeGlyphs

  /**
   * Create an 8-bit palettized surface and render the given text at fast quality with the given
   * font and color. The 0 pixel is the colorkey, giving a transparent background, and the 1 pixel
   * is set to the text color.
   *
   * \param text  The text to render.
   * \param color The color of the text.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderText_Solid
   * \upstream TTF_RenderUTF8_Solid
   * \upstream TTF_RenderUNICODE_Solid
   */
  Surface RenderSolid(const std::string& text, Color color);
  Surface RenderSolidUTF8(const std::string& text, Color color);
  Surface RenderSolidUnicode(const std::u16string& text, Color color);

  /**
   * Create an 8-bit palettized surface and render the given glyph at fast quality with the given
   * font and color. The 0 pixel is the colorkey, giving a transparent background, and the 1 pixel
   * is set to the text color. The glyph is rendered without any padding or centering in the X
   * direction, and aligned normally in the Y direction.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderGlyph_Solid
   */
  Surface RenderSolid(char16_t c, Color color);

  /**
   * Create an 8-bit palettized surface and render the given text at high quality with the given
   * font and colors. The 0 pixel is background, while other pixels have varying degrees of the
   * foreground color.
   *
   * \param text     The text to render.
   * \param color    The color of the text.
   * \param bgcolor  The color of the background.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderText_Shaded
   * \upstream TTF_RenderUTF8_Shaded
   * \upstream TTF_RenderUNICODE_Shaded
   */
  Surface RenderShaded(const std::string& text, Color color, Color bgcolor);
  Surface RenderShadedUTF8(const std::string& text, Color color, Color bgcolor);
  Surface RenderShadedUnicode(const std::u16string& text, Color color, Color bgcolor);

  /**
   * Create an 8-bit palettized surface and render the given glyph at high quality with the given
   * font and colors. The 0 pixel is background, while other pixels have varying degrees of the
   * foreground color. The glyph is rendered without any padding or centering in the X direction,
   * and aligned normally in the Y direction.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderGlyph_Shaded
   */
  Surface RenderShaded(char16_t c, Color color, Color bgcolor);

  /**
   * Create a 32-bit ARGB surface and render the given text at high quality, using alpha blending to
   * dither the font with the given color.
   *
   * \param text    The text to render.
   * \param color   The color of the text.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderText_Blended
   * \upstream TTF_RenderUTF8_Blended
   * \upstream TTF_RenderUNICODE_Blended
   */
  Surface RenderBlended(const std::string& text, Color color);
  Surface RenderBlendedUTF8(const std::string& text, Color color);
  Surface RenderBlendedUnicode(const std::u16string& text, Color color);

  /**
   * Create a 32-bit ARGB surface and render the given glyph at high quality, using alpha blending
   * to dither the font with the given color. The glyph is rendered without any padding or centering
   * in the X direction, and aligned normally in the Y direction.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderGlyph_Blended
   */
  Surface RenderBlended(char16_t c, Color color);

  /**
   * Create a 32-bit ARGB surface and render the given text at high quality, using alpha blending to
   * dither the font with the given color.
   *
   * Text is wrapped to multiple lines on line endings and on word boundaries if it extends beyond
   * wrap_length in pixels.
   *
   * \param text    The text to render.
   * \param color   The color of the text.
   * \param wrap_length The wrap length in pixels.
   *
   * \throw FontException if there was an error.
   *
   * \upstream TTF_RenderText_Blended_Wrapped
   * \upstream TTF_RenderUTF8_Blended_Wrapped
   * \upstream TTF_RenderUNICODE_Blended_Wrapped
   */
  Surface RenderBlended(const std::string& text, Color color, uint32_t wrap_length);
  Surface RenderBlendedUTF8(const std::string& text, Color color, uint32_t wrap_length);
  Surface RenderBlendedUnicode(const std::u16string& text, Color color, uint32_t wrap_length);

private:
  struct Deleter {
    /**
     * \brief Close an opened font file
     *
     * \upstream TTF_CloseFont
     */
    void operator()(TTF_Font* ptr) const;
  };

  std::unique_ptr<TTF_Font, Deleter> font_ptr;
};

}  // namespace sdlxx

ENABLE_BITMASK_OPERATORS(sdlxx::Font::Style);

#endif  // SDLXX_TTF_FONT_H
