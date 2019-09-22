#ifndef SDLXX_TEXTURE_H
#define SDLXX_TEXTURE_H

#include <string>
#include <SDL_render.h>
#include <SDL_image.h>
#include "../ttf/Font.h"
#include "Log.h"

namespace SDLXX {
    class Texture {
    public:
        Texture(SDL_Texture *t);

        Texture(const std::string &path, SDL_Renderer *renderer, int w, int h);

        Texture(const std::string &text, const Color &color, const Font &font, SDL_Renderer *renderer);

        ~Texture();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode(SDL_BlendMode blending);

        void setAlpha(Uint8 alpha);

        //Renders texture at given point
        void render(SDL_Renderer *renderer, SDL_Rect *clip = nullptr, SDL_Rect *dest = nullptr, double angle = 0.0,
                    SDL_Point *center = nullptr,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

        void fill(SDL_Renderer *renderer, SDL_Rect *clip = nullptr, SDL_Rect *dest = nullptr, double angle = 0.0,
                    SDL_Point *center = nullptr,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth() const;

        int getHeight() const;

        SDL_Texture *getSDLTexture() const;

    private:
        SDL_Texture *texture = nullptr;
        int width = 0;
        int height = 0;
        int access = SDL_TEXTUREACCESS_STATIC;
        Uint32 format = SDL_PIXELFORMAT_UNKNOWN;
    };
}

#endif // SDLXX_TEXTURE_H
