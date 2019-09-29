#include <sdlxx/ttf/Font.h>

sdlxx::ttf::Font::Font(TTF_Font *f) {
    font = f;
}

sdlxx::ttf::Font::Font(const std::string &path, int ptsize, int index) {
    if((font = TTF_OpenFontIndex(path.c_str(), ptsize, index)) == nullptr) {
        throw std::runtime_error("Failed to load font" + std::string(TTF_GetError()));
    }
}

sdlxx::ttf::Font::Font(sdlxx::ttf::Font &&other) noexcept : font(other.font) {
    other.font = nullptr;
}

sdlxx::ttf::Font &sdlxx::ttf::Font::operator=(sdlxx::ttf::Font &&other) noexcept {
    if(&other != this) {
        if(font != nullptr) {
            TTF_CloseFont(font);
        }
        font = other.font;
        other.font = nullptr;
    }
    return *this;
}

TTF_Font *sdlxx::ttf::Font::getSDLFont() const {
    return font;
}

sdlxx::ttf::Font::~Font() {
    if(font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

sdlxx::core::Surface
sdlxx::ttf::Font::render(const std::string &text, int mode, const sdlxx::core::Color &color, const sdlxx::core::Color &bg) const {
    SDL_Surface *sdlSurface = nullptr;
    switch (mode) {
        case TTF_MODE_BLENDED:
            sdlSurface = TTF_RenderUTF8_Blended(font, text.c_str(), {color.red, color.green, color.blue, color.alpha});
            break;
        case TTF_MODE_SHADED:
            sdlSurface = TTF_RenderUTF8_Shaded(font, text.c_str(), {color.red, color.green, color.blue, color.alpha}, {bg.red, bg.green, bg.blue, bg.alpha});
            break;
        case TTF_MODE_SOLID:
        default:
            sdlSurface = TTF_RenderUTF8_Solid(font, text.c_str(), {color.red, color.green, color.blue, color.alpha});
            break;
    }
    if(sdlSurface == nullptr) {
        throw std::runtime_error("Unable to render text" + std::string(TTF_GetError()));
    }
    return sdlxx::core::Surface(sdlSurface);
}

sdlxx::core::Surface sdlxx::ttf::Font::render(Uint16 ch, int mode, const sdlxx::core::Color &color, const sdlxx::core::Color &bg) const {
    SDL_Surface *sdlSurface = nullptr;
    switch (mode) {
        case TTF_MODE_BLENDED:
            sdlSurface = TTF_RenderGlyph_Blended(font, ch, {color.red, color.green, color.blue, color.alpha});
            break;
        case TTF_MODE_SHADED:
            sdlSurface = TTF_RenderGlyph_Shaded(font, ch, {color.red, color.green, color.blue, color.alpha}, {bg.red, bg.green, bg.blue, bg.alpha});
            break;
        case TTF_MODE_SOLID:
        default:
            sdlSurface = TTF_RenderGlyph_Solid(font, ch, {color.red, color.green, color.blue, color.alpha});
            break;
    }
    if(sdlSurface == nullptr) {
        throw std::runtime_error("Unable to render glyph" + std::string(TTF_GetError()));
    }
    return sdlxx::core::Surface(sdlSurface);
}
