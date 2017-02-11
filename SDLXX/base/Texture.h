#ifndef SDLXX_TEXTURE_H
#define SDLXX_TEXTURE_H

#include <string>
#include <SDL_render.h>
#include <SDL_image.h>
#include "../ttf/Font.h"

namespace SDLXX {
    class Texture {
    public:
        Texture(SDL_Texture *t) {
            texture = t;
            SDL_QueryTexture(t, &format, &access, &width, &height);
        }

        Texture(const std::string &path, SDL_Renderer *renderer) {
            SDL_Surface *surface = IMG_Load(path.c_str());
            if(surface == nullptr) {
                throw Exception("Unable to load image", IMG_GetError());
            }
            SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF)); // FIXME: For what?
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if(texture == nullptr) {
                throw Exception("Unable to create texture", SDL_GetError());
            }
            width = surface->w;
            height = surface->h;
            SDL_FreeSurface(surface);
        }

        Texture(const std::string &text, const Color &color, const Font &font, SDL_Renderer *renderer) {
            Surface surface = font.render(text, TTF_MODE_BLENDED, color);
            texture = SDL_CreateTextureFromSurface(renderer, surface.getSDLSurface());
            if(texture == nullptr) {
                throw Exception("Unable to create texture", SDL_GetError());
            }
            width = surface.getWidth();
            height = surface.getHeight();
        }

        ~Texture() {
            if(texture != nullptr) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
                width = 0;
                height = 0;
                access = SDL_TEXTUREACCESS_STATIC;
                format = SDL_PIXELFORMAT_UNKNOWN;
            }
        }

        void setColor(Uint8 red, Uint8 green, Uint8 blue) {
            SDL_SetTextureColorMod(texture, red, green, blue);
        }

        void setBlendMode(SDL_BlendMode blending) {
            SDL_SetTextureBlendMode(texture, blending);
        }

        void setAlpha(Uint8 alpha) {
            SDL_SetTextureAlphaMod(texture, alpha);
        }

        //Renders texture at given point
        void render(SDL_Renderer *renderer, int x = 0, int y = 0, SDL_Rect *clip = nullptr, double angle = 0.0,
                    SDL_Point *center = nullptr,
                    SDL_RendererFlip flip = SDL_FLIP_NONE) {
            //Set rendering space and render to screen
            SDL_Rect renderQuad = {x, y, width, height};

            //Set clip rendering dimensions
            if(clip != nullptr) {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
            }

            //Render to screen
            SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
        }

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }

        SDL_Texture *getSDLTexture() const {
            return texture;
        }

    private:
        SDL_Texture *texture = nullptr;
        int width = 0;
        int height = 0;
        int access = SDL_TEXTUREACCESS_STATIC;
        Uint32 format = SDL_PIXELFORMAT_UNKNOWN;
    };
}

#endif // SDLXX_TEXTURE_H
