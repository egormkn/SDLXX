#include "sdlxx/ttf/font.h"

#include <SDL_ttf.h>

using namespace sdlxx::core;
using namespace sdlxx::ttf;

Font::Font(TTF_Font* ptr) : font_ptr(ptr) {
  if (!font_ptr) {
    throw FontException("Failed to initialize a font");
  }
}

Font::Font(const std::string& path, int point_size, int index)
    : Font(TTF_OpenFontIndex(path.c_str(), point_size, index)) {}

BitMask<Font::Style> Font::GetStyle() const {
  return BitMask<Font::Style>{TTF_GetFontStyle(font_ptr.get())};
}

void Font::SetStyle(sdlxx::core::BitMask<Style> style) {
  TTF_SetFontStyle(font_ptr.get(), style.value);
}

int Font::GetOutline() const { return TTF_GetFontOutline(font_ptr.get()); }

void Font::SetOutline(int outline) { TTF_SetFontOutline(font_ptr.get(), outline); }

Font::Hinting Font::GetHinting() const {
  return static_cast<Hinting>(TTF_GetFontHinting(font_ptr.get()));
}
void Font::SetHinting(Font::Hinting hinting) {
  TTF_SetFontHinting(font_ptr.get(), static_cast<int>(hinting));
}

Surface Font::RenderSolid(const std::string& text, Color color) {
  SDL_Surface* ptr =
      TTF_RenderText_Solid(font_ptr.get(), text.c_str(), {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderSolidUTF8(const std::string& text, Color color) {
  SDL_Surface* ptr =
      TTF_RenderUTF8_Solid(font_ptr.get(), text.c_str(), {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderSolidUnicode(const std::u16string& text, Color color) {
  SDL_Surface* ptr =
      TTF_RenderUNICODE_Solid(font_ptr.get(), reinterpret_cast<const Uint16*>(text.c_str()),
                              {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderSolid(char16_t c, Color color) {
  SDL_Surface* ptr = TTF_RenderGlyph_Solid(font_ptr.get(), c, {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderShaded(const std::string& text, Color color, Color bgcolor) {
  SDL_Surface* ptr =
      TTF_RenderText_Shaded(font_ptr.get(), text.c_str(), {color.r, color.g, color.b, color.a},
                            {bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a});
  return Surface(ptr);
}

Surface Font::RenderShadedUTF8(const std::string& text, Color color, Color bgcolor) {
  SDL_Surface* ptr =
      TTF_RenderUTF8_Shaded(font_ptr.get(), text.c_str(), {color.r, color.g, color.b, color.a},
                            {bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a});
  return Surface(ptr);
}

Surface Font::RenderShadedUnicode(const std::u16string& text, Color color, Color bgcolor) {
  SDL_Surface* ptr = TTF_RenderUNICODE_Shaded(
      font_ptr.get(), reinterpret_cast<const Uint16*>(text.c_str()),
      {color.r, color.g, color.b, color.a}, {bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a});
  return Surface(ptr);
}

Surface Font::RenderShaded(char16_t c, Color color, Color bgcolor) {
  SDL_Surface* ptr = TTF_RenderGlyph_Shaded(font_ptr.get(), c, {color.r, color.g, color.b, color.a},
                                            {bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a});
  return Surface(ptr);
}

Surface Font::RenderBlended(const std::string& text, Color color) {
  SDL_Surface* ptr =
      TTF_RenderText_Blended(font_ptr.get(), text.c_str(), {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderBlendedUTF8(const std::string& text, Color color) {
  SDL_Surface* ptr =
      TTF_RenderUTF8_Blended(font_ptr.get(), text.c_str(), {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderBlendedUnicode(const std::u16string& text, Color color) {
  SDL_Surface* ptr =
      TTF_RenderUNICODE_Blended(font_ptr.get(), reinterpret_cast<const Uint16*>(text.c_str()),
                                {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderBlended(char16_t c, Color color) {
  SDL_Surface* ptr =
      TTF_RenderGlyph_Blended(font_ptr.get(), c, {color.r, color.g, color.b, color.a});
  return Surface(ptr);
}

Surface Font::RenderBlended(const std::string& text, Color color, uint32_t wrap_length) {
  SDL_Surface* ptr = TTF_RenderText_Blended_Wrapped(font_ptr.get(), text.c_str(),
                                                    {color.r, color.g, color.b, color.a},
                                                    static_cast<Uint32>(wrap_length));
  return Surface(ptr);
}

Surface Font::RenderBlendedUTF8(const std::string& text, Color color, uint32_t wrap_length) {
  SDL_Surface* ptr = TTF_RenderUTF8_Blended_Wrapped(font_ptr.get(), text.c_str(),
                                                    {color.r, color.g, color.b, color.a},
                                                    static_cast<Uint32>(wrap_length));
  return Surface(ptr);
}

Surface Font::RenderBlendedUnicode(const std::u16string& text, Color color, uint32_t wrap_length) {
  SDL_Surface* ptr = TTF_RenderUNICODE_Blended_Wrapped(
      font_ptr.get(), reinterpret_cast<const Uint16*>(text.c_str()),
      {color.r, color.g, color.b, color.a}, static_cast<Uint32>(wrap_length));
  return Surface(ptr);
}

void Font::Deleter::operator()(TTF_Font* ptr) const {
  if (ptr != nullptr) {
    TTF_CloseFont(ptr);
  }
}
