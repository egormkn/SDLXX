#ifndef SDLXX_RENDERER_H
#define SDLXX_RENDERER_H

#include <SDL_render.h>
#include "../Exception.h"
#include "Color.h"

namespace SDLXX {
    class Renderer {
    public:
        Renderer(SDL_Renderer *r) : renderer(r) {}

        Renderer(SDL_Window *w, int driver, Uint32 flags) {
            renderer = SDL_CreateRenderer(w, driver, flags);
            if(renderer == nullptr) {
                throw Exception("Renderer could not be created");
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

    private:
        SDL_Renderer *renderer = nullptr;
    };
}

#endif // SDLXX_RENDERER_H
