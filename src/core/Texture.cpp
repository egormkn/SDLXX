#include <stdexcept>

#include <SDL_render.h>
#include <sdlxx/core/Color.h>
#include <sdlxx/core/Renderer.h>
#include <sdlxx/core/Surface.h>
#include <sdlxx/core/Texture.h>

using namespace sdlxx::core;

using Format = Texture::Format;
using Access = Texture::Access;

Texture::Texture(std::shared_ptr<Renderer> renderer, int width, int height,
                 Format format, Access access) {
  texture_ptr =
      SDL_CreateTexture(static_cast<SDL_Renderer*>(renderer->renderer_ptr),
                        format, static_cast<int>(access), width, height);
  if (!texture_ptr) {
    throw std::runtime_error("Failed to create texture: " +
                             std::string(SDL_GetError()));
  }
}

Texture::Texture(std::shared_ptr<Renderer> renderer, const Surface& surface) {
  texture_ptr = SDL_CreateTextureFromSurface(
      static_cast<SDL_Renderer*>(renderer->renderer_ptr),
      static_cast<SDL_Surface*>(surface.surface_ptr));
  if (!texture_ptr) {
    throw std::runtime_error("Failed to create texture from surface: " +
                             std::string(SDL_GetError()));
  }
}

Texture::~Texture() {
  if (texture_ptr) {
    SDL_DestroyTexture(static_cast<SDL_Texture*>(texture_ptr));
    texture_ptr = nullptr;
  }
}

std::tuple<Dimensions, Format, Access> Texture::query() const {
  Uint32 format;
  int access, width, height;
  int return_code = SDL_QueryTexture(static_cast<SDL_Texture*>(texture_ptr),
                                     &format, &access, &width, &height);
  if (return_code != 0) {
    throw std::runtime_error("Failed to get texture data: " +
                             std::string(SDL_GetError()));
  }
  Dimensions dimensions(width, height);
  return {dimensions, format, static_cast<Access>(access)};
}

Dimensions Texture::getDimensions() const { return std::get<0>(query()); }

uint32_t Texture::getFormat() const { return std::get<1>(query()); }

Access Texture::getAccess() const { return std::get<2>(query()); }

void Texture::setModulation(const Color& color) {
  if (color.r != 0 && color.g != 0 && color.b != 0) {
    int return_code = SDL_SetTextureColorMod(
        static_cast<SDL_Texture*>(texture_ptr), color.r, color.g, color.b);
    if (return_code != 0) {
      throw std::runtime_error("Failed to set texture color modulation: " +
                               std::string(SDL_GetError()));
    }
  }
  if (color.a != 0) {
    int return_code =
        SDL_SetTextureAlphaMod(static_cast<SDL_Texture*>(texture_ptr), color.a);
    if (return_code != 0) {
      throw std::runtime_error("Failed to set texture alpha modulation: " +
                               std::string(SDL_GetError()));
    }
  }
}

Color Texture::getModulation() const {
  Uint8 r, g, b, a;
  {
    int return_code = SDL_GetTextureColorMod(
        static_cast<SDL_Texture*>(texture_ptr), &r, &g, &b);
    if (return_code != 0) {
      throw std::runtime_error("Failed to get texture color modulation: " +
                               std::string(SDL_GetError()));
    }
  }
  {
    int return_code =
        SDL_GetTextureAlphaMod(static_cast<SDL_Texture*>(texture_ptr), &a);
    if (return_code != 0) {
      throw std::runtime_error("Failed to get texture alpha modulation: " +
                               std::string(SDL_GetError()));
    }
  }
  return {r, g, b, a};
}
