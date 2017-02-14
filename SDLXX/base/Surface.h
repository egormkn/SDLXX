#ifndef SDLXX_SURFACE_H
#define SDLXX_SURFACE_H

#include <SDL_surface.h>

namespace SDLXX {
    class Surface {
    public:
        Surface(SDL_Surface *s) {
            surface = s;
        }

        ~Surface() {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        SDL_Surface *getSDLSurface() const {
            return surface;
        }

        int getWidth() const {
            return surface->w;
        }

        int getHeight() const {
            return surface->h;
        }

    private:
        SDL_Surface *surface = nullptr;
    };
}

#endif // SDLXX_SURFACE_H
