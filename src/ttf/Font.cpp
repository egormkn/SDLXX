#include <SDL_ttf.h>
#include <sdlxx/ttf/Font.h>

using namespace sdlxx::core;
using namespace sdlxx::ttf;

Font::Font(void* font_ptr) : font_ptr(font_ptr) {}

Font::Font(const std::string& file, int point_size, int index) {
  font_ptr = TTF_OpenFontIndex(file.c_str(), point_size, index);
  if (!font_ptr) {
    throw std::runtime_error("Failed to load font: " +
                             std::string(TTF_GetError()));
  }
}

Font::~Font() {
  if (font_ptr) {
    TTF_CloseFont(static_cast<TTF_Font*>(font_ptr));
    font_ptr = nullptr;
  }
}

Surface Font::render(const std::string& text, int mode, const Color& color,
                     const Color& bg) const {
  SDL_Surface* sdlSurface = nullptr;
  switch (mode) {
    case TTF_MODE_BLENDED:
      sdlSurface = TTF_RenderUTF8_Blended(
          static_cast<TTF_Font*>(font_ptr), text.c_str(),
          {color.red, color.green, color.blue, color.alpha});
      break;
    case TTF_MODE_SHADED:
      sdlSurface = TTF_RenderUTF8_Shaded(
          static_cast<TTF_Font*>(font_ptr), text.c_str(), {color.red, color.green, color.blue, color.alpha},
          {bg.red, bg.green, bg.blue, bg.alpha});
      break;
    case TTF_MODE_SOLID:
    default:
      sdlSurface = TTF_RenderUTF8_Solid(
          static_cast<TTF_Font*>(font_ptr), text.c_str(),
          {color.red, color.green, color.blue, color.alpha});
      break;
  }
  if (sdlSurface == nullptr) {
    throw std::runtime_error("Unable to render text" +
                             std::string(TTF_GetError()));
  }
  return Surface(sdlSurface);
}

Surface Font::render(wchar_t ch, int mode, const Color& color,
                     const Color& bg) const {
  SDL_Surface* sdlSurface = nullptr;
  switch (mode) {
    case TTF_MODE_BLENDED:
      sdlSurface = TTF_RenderGlyph_Blended(
          static_cast<TTF_Font*>(font_ptr), static_cast<Uint16>(ch), {color.red, color.green, color.blue, color.alpha});
      break;
    case TTF_MODE_SHADED:
      sdlSurface = TTF_RenderGlyph_Shaded(
          static_cast<TTF_Font*>(font_ptr), static_cast<Uint16>(ch), {color.red, color.green, color.blue, color.alpha},
          {bg.red, bg.green, bg.blue, bg.alpha});
      break;
    case TTF_MODE_SOLID:
    default:
      sdlSurface = TTF_RenderGlyph_Solid(
          static_cast<TTF_Font*>(font_ptr), static_cast<Uint16>(ch), {color.red, color.green, color.blue, color.alpha});
      break;
  }
  if (sdlSurface == nullptr) {
    throw std::runtime_error("Unable to render glyph: " +
                             std::string(TTF_GetError()));
  }
  return Surface(sdlSurface);
}
