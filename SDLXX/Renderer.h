#ifndef SDLXX_RENDERER_H
#define SDLXX_RENDERER_H

#include <SDL_render.h>
#include "Window.h"
#include "Exception.h"

namespace SDL {
    class Renderer {
    public:
        Renderer(Window &window, int driver, Uint32 flags) {
            renderer = SDL_CreateRenderer(window.getWindow(), driver, flags);
            if(renderer == NULL) {
                throw Exception("Renderer could not be created");
            }
        }

        ~Renderer() {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;
        }

        SDL_Renderer *getRenderer() {
            return renderer;
        }

    private:
        SDL_Renderer *renderer = NULL;
    };
}

#endif // SDLXX_RENDERER_H
