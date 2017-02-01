#ifndef SDLXX_RENDERER_H
#define SDLXX_RENDERER_H

#include <SDL_render.h>
#include "../Exception.h"
#include "Color.h"
#include "../Log.h"
#include "Texture.h"
#include "Rectangle.h"

namespace SDLXX {
    class Renderer {
    public:
        Renderer(SDL_Renderer *r) : renderer(r) {}

        Renderer(SDL_Window *w, int driver, Uint32 flags) {
            renderer = SDL_CreateRenderer(w, driver, flags);
            if(renderer == nullptr) {
                Log::warning("Could not create hardware accelerated renderer, trying software fallback");
                renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
                if(renderer == nullptr) {
                    throw Exception("Renderer could not be created", SDL_GetError());
                }
            }
        }

        ~Renderer() {
            if(renderer != nullptr) {
                SDL_DestroyRenderer(renderer);
                renderer = nullptr;
            }
        }

        SDL_Renderer *getSDLRenderer() const {
            return renderer;
        }

        void setColor(const Color &color) {
            SDL_SetRenderDrawColor(renderer, color.r(), color.g(), color.b(), color.a());
        }

        void render() {
            SDL_RenderPresent(renderer);
        }

        void clear() {
            SDL_RenderClear(renderer);
        }

        void renderCopy(const Texture &texture) {
            int result = SDL_RenderCopy(renderer, texture.getSDLTexture(), NULL, NULL);
            if (result < 0) {
                throw Exception("Failed to render a texture");
            }
        }

        void renderCopy(const Texture &texture, const Rectangle &src, const Rectangle &dest) {
            int result = SDL_RenderCopy(renderer, texture.getSDLTexture(), src.getSDLRectangle(), dest.getSDLRectangle());
            if (result < 0) {
                throw Exception("Failed to render a texture");
            }
        }

    private:
        SDL_Renderer *renderer = nullptr;
    };
}

#endif // SDLXX_RENDERER_H
