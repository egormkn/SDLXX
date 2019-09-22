//
// Created by egorm on 09.02.2017.
//

#include <sdlxx/core/Surface.h>

sdlxx::core::Surface::Surface(SDL_Surface *s) {
    surface = s;
}

sdlxx::core::Surface::~Surface() {
    SDL_FreeSurface(surface);
    surface = nullptr;
}

SDL_Surface *sdlxx::core::Surface::getSDLSurface() const {
    return surface;
}

int sdlxx::core::Surface::getWidth() const {
    return surface->w;
}

int sdlxx::core::Surface::getHeight() const {
    return surface->h;
}
