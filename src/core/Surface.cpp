
#include <SDL_surface.h>
#include <sdlxx/core/Surface.h>

using namespace sdlxx::core;

Surface::Surface(void* surface_ptr) : surface_ptr(surface_ptr) {}

Surface::~Surface() {
  SDL_FreeSurface(static_cast<SDL_Surface*>(surface_ptr));
  surface_ptr = nullptr;
}

Dimensions Surface::getSize() const {
  int width = static_cast<SDL_Surface*>(surface_ptr)->w;
  int height = static_cast<SDL_Surface*>(surface_ptr)->h;
  return {static_cast<unsigned>(width), static_cast<unsigned>(height)};
}

Surface Surface::fromBMP(const std::string& file) {
  SDL_Surface* surface_ptr = SDL_LoadBMP(file.c_str());
  return {surface_ptr};
}
