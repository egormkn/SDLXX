//
// Created by egorm on 09.02.2017.
//

#include "Surface.h"

SDLXX::Surface::Surface(SDL_Surface *s) {
    surface = s;
}

SDLXX::Surface::~Surface() {
    SDL_FreeSurface(surface);
    surface = nullptr;
}

SDL_Surface *SDLXX::Surface::getSDLSurface() const {
    return surface;
}

int SDLXX::Surface::getWidth() const {
    return surface->w;
}

int SDLXX::Surface::getHeight() const {
    return surface->h;
}
