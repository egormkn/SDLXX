
#include <SDL_surface.h>
#include <sdlxx/core/Surface.h>

using namespace sdlxx::core;

Surface::Surface(void* surface_ptr) : surface_ptr(surface_ptr) {}

Surface::~Surface() {
  if (surface_ptr) {
    SDL_FreeSurface(static_cast<SDL_Surface*>(surface_ptr));
    surface_ptr = nullptr;
  }
}

Dimensions Surface::getSize() const {
  SDL_Surface* surface = static_cast<SDL_Surface*>(surface_ptr);
  return {surface->w, surface->h};
}

Surface Surface::fromBMP(const std::string& file) {
  SDL_Surface* surface_ptr = SDL_LoadBMP(file.c_str());
  return {surface_ptr};
}
