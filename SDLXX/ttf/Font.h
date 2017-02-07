#ifndef SDLXX_FONT_H
#define SDLXX_FONT_H

#include <SDLXX/Exception.h>
#include "SDLXX_ttf.h"

namespace SDLXX {
    class Font {
    public:
        Font(const std::string &path, int ptsize, int index = 0) {
            font = TTF_OpenFontIndex(path.c_str(), ptsize, index);
            if(font == nullptr) {
                throw Exception("Failed to load font", TTF_GetError());
            }
        }

        Font(SDL_RWops *src, int freesrc, int ptsize, int index = 0)  {
            font = TTF_OpenFontIndexRW(src, freesrc, ptsize, index);
            if(font == nullptr) {
                throw Exception("Failed to load font", TTF_GetError());
            }
        }

        ~Font() {
            if(font != nullptr) {
                TTF_CloseFont(font);
                font = nullptr;
            }
        }

    private:
        TTF_Font *font = nullptr;
    };
}

#endif // SDLXX_FONT_H


/*
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
3.4 Render
3.4.1 TTF_RenderText_Solid
3.4.2 TTF_RenderUTF8_Solid
3.4.3 TTF_RenderUNICODE_Solid
3.4.4 TTF_RenderGlyph_Solid
3.4.5 TTF_RenderText_Shaded
3.4.6 TTF_RenderUTF8_Shaded
3.4.7 TTF_RenderUNICODE_Shaded
3.4.8 TTF_RenderGlyph_Shaded
3.4.9 TTF_RenderText_Blended
3.4.10 TTF_RenderUTF8_Blended
3.4.11 TTF_RenderUNICODE_Blended
3.4.12 TTF_RenderGlyph_Blended
 */