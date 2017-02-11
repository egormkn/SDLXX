#ifndef SDLXX_FONT_H
#define SDLXX_FONT_H

#include "SDLXX_ttf.h"
#include "../Exception.h"
#include "../base/Surface.h"
#include "../base/Color.h"

namespace SDLXX {
    enum {
        TTF_MODE_SOLID,
        TTF_MODE_SHADED,
        TTF_MODE_BLENDED
    };

    class Font {
    public:
        Font(TTF_Font *f) {
            font = f;
        }

        Font(const std::string &path, int ptsize, int index = 0) {
            if((font = TTF_OpenFontIndex(path.c_str(), ptsize, index)) == nullptr) {
                throw Exception("Failed to load font", TTF_GetError());
            }
        }

        Font(Font &&other) noexcept : font(other.font) {
            other.font = nullptr;
        }

        Font &operator=(Font &&other) noexcept {
            if(&other != this) {
                if(font != nullptr) {
                    TTF_CloseFont(font);
                }
                font = other.font;
                other.font = nullptr;
            }
            return *this;
        }

        Font(const Font &) = delete;

        Font &operator=(const Font &) = delete;

        TTF_Font *getSDLFont() const {
            return font;
        }

        ~Font() {
            if(font != nullptr) {
                TTF_CloseFont(font);
                font = nullptr;
            }
        }

        Surface render(const std::string &text, int mode,
                       const Color &color, const Color &bg = Color(0x00000000)) const {
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

        Surface render(Uint16 ch, int mode, const Color &color, const Color &bg = Color(0x00000000)) const {
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

        // TODO: Open font by file descriptor
        // TODO: Get font properties
        /**
        3.3.1 TTF_ByteSwappedUNICODE
        3.3.2 TTF_GetFontStyle
        3.3.3 TTF_SetFontStyle
        3.3.4 TTF_GetFontOutline
        3.3.5 TTF_SetFontOutline
        3.3.6 TTF_GetFontHinting
        3.3.7 TTF_SetFontHinting
        3.3.8 TTF_GetFontKerning
        3.3.9 TTF_SetFontKerning
        3.3.10 TTF_FontHeight
        3.3.11 TTF_FontAscent
        3.3.12 TTF_FontDescent
        3.3.13 TTF_FontLineSkip
        3.3.14 TTF_FontFaces
        3.3.15 TTF_FontFaceIsFixedWidth
        3.3.16 TTF_FontFaceFamilyName
        3.3.17 TTF_FontFaceStyleName
        3.3.18 TTF_GlyphIsProvided
        3.3.19 TTF_GlyphMetrics
        3.3.20 TTF_SizeText
        3.3.21 TTF_SizeUTF8
        3.3.22 TTF_SizeUNICODE
        */

    private:
        TTF_Font *font = nullptr;
    };
}

#endif // SDLXX_FONT_H