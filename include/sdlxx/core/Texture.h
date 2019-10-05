/**
 * @file Texture.h
 * @author Egor Makarenko
 * @brief Class that represents a texture in an efficient driver-specific way
 */

#pragma once

#ifndef SDLXX_CORE_TEXTURE_H
#define SDLXX_CORE_TEXTURE_H

#include <string>

#include <SDL_image.h>
#include <SDL_render.h>
#include <sdlxx/core/Log.h>
#include <sdlxx/core/Renderer.h>
#include <sdlxx/ttf/Font.h>

namespace sdlxx::core {

class Renderer;

/**
 * @brief Class that represents a texture in an efficient driver-specific way
 */
class Texture {
public:
  Texture(const std::string& path, const std::shared_ptr<Renderer>& renderer, int w, int h);

  Texture(const std::string& text, const Color& color,
          const sdlxx::ttf::Font& font, const std::shared_ptr<Renderer>& renderer);

  ~Texture();

  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  void setBlendMode(SDL_BlendMode blending);

  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(SDL_Renderer* renderer, SDL_Rect* clip = nullptr,
              SDL_Rect* dest = nullptr, double angle = 0.0,
              SDL_Point* center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  void fill(SDL_Renderer* renderer, SDL_Rect* clip = nullptr,
            SDL_Rect* dest = nullptr, double angle = 0.0,
            SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

  int getWidth() const;

  int getHeight() const;

  SDL_Texture* getSDLTexture() const;

  friend class Renderer;

private:
  void* texture_ptr = nullptr;
  int width = 0;
  int height = 0;
  int access = SDL_TEXTUREACCESS_STATIC;
  Uint32 format = SDL_PIXELFORMAT_UNKNOWN;

  Texture(void* texture_ptr);

  // Deleted copy constructor
  // This class is not copyable
  Texture(const Texture&) = delete;

  // Deleted copy assignment operator
  // This class is not copyable
  void operator=(const Texture&) = delete;
};
}  // namespace sdlxx::core

#endif  // SDLXX_TEXTURE_H
