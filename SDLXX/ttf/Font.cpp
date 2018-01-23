#include "Font.h"

SDLXX::Font::Font(TTF_Font *f) {
    font = f;
}

SDLXX::Font::Font(const std::string &path, int ptsize, int index) {
    if((font = TTF_OpenFontIndex(path.c_str(), ptsize, index)) == nullptr) {
        throw Exception("Failed to load font", TTF_GetError());
    }
}

SDLXX::Font::Font(SDLXX::Font &&other) noexcept : font(other.font) {
    other.font = nullptr;
}

SDLXX::Font &SDLXX::Font::operator=(SDLXX::Font &&other) noexcept {
    if(&other != this) {
        if(font != nullptr) {
            TTF_CloseFont(font);
        }
        font = other.font;
        other.font = nullptr;
    }
    return *this;
}

TTF_Font *SDLXX::Font::getSDLFont() const {
    return font;
}

SDLXX::Font::~Font() {
    if(font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

SDLXX::Surface
SDLXX::Font::render(const std::string &text, int mode, const SDLXX::Color &color, const SDLXX::Color &bg) const {
    SDL_Surface *sdlSurface = nullptr;
    switch (mode) {
        case TTF_MODE_BLENDED:
            sdlSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color.getSDLColor());
            break;
        case TTF_MODE_SHADED:
            sdlSurface = TTF_RenderUTF8_Shaded(font, text.c_str(), color.getSDLColor(), bg.getSDLColor());
            break;
        case TTF_MODE_SOLID:
        default:
            sdlSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color.getSDLColor());
            break;
    }
    if(sdlSurface == nullptr) {
        throw Exception("Unable to render text", TTF_GetError());
    }
    return Surface(sdlSurface);
}

SDLXX::Surface SDLXX::Font::render(Uint16 ch, int mode, const SDLXX::Color &color, const SDLXX::Color &bg) const {
    SDL_Surface *sdlSurface = nullptr;
    switch (mode) {
        case TTF_MODE_BLENDED:
            sdlSurface = TTF_RenderGlyph_Blended(font, ch, color.getSDLColor());
            break;
        case TTF_MODE_SHADED:
            sdlSurface = TTF_RenderGlyph_Shaded(font, ch, color.getSDLColor(), bg.getSDLColor());
            break;
        case TTF_MODE_SOLID:
        default:
            sdlSurface = TTF_RenderGlyph_Solid(font, ch, color.getSDLColor());
            break;
    }
    if(sdlSurface == nullptr) {
        throw Exception("Unable to render glyph", TTF_GetError());
    }
    return Surface(sdlSurface);
}
