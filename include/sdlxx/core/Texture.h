/**
 * @file Texture.h
 * @author Egor Makarenko
 * @brief Class that represents a texture
 */

#pragma once

#ifndef SDLXX_CORE_TEXTURE_H
#define SDLXX_CORE_TEXTURE_H

#include <string>

#include <SDL_image.h>
#include <SDL_render.h>
#include <sdlxx/core/Renderer.h>

#include "../ttf/Font.h"
#include "Log.h"

namespace sdlxx::core {

class Renderer;

class Texture {
public:
  Texture(SDL_Texture* t);

  Texture(const std::string& path, const Renderer& renderer, int w, int h);

  Texture(const std::string& text, const Color& color,
          const sdlxx::ttf::Font& font, const Renderer& renderer);

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

private:
  SDL_Texture* texture = nullptr;
  int width = 0;
  int height = 0;
  int access = SDL_TEXTUREACCESS_STATIC;
  Uint32 format = SDL_PIXELFORMAT_UNKNOWN;
};
}  // namespace sdlxx::core

#endif  // SDLXX_TEXTURE_H
