#ifndef SDLXX_SURFACE_H
#define SDLXX_SURFACE_H

#include <SDL_surface.h>

namespace sdlxx::core {
    class Surface {
    public:
        Surface(SDL_Surface *s);

        ~Surface();

        SDL_Surface *getSDLSurface() const;

        int getWidth() const;

        int getHeight() const;

    private:
        SDL_Surface *surface = nullptr;
    };
}

#endif // SDLXX_SURFACE_H
