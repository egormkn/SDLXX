/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the Texture class that represents a texture.
 */

#pragma once

#ifndef SDLXX_CORE_TEXTURE_H
#define SDLXX_CORE_TEXTURE_H

#include <string>

#include "sdlxx/core/renderer.h"

// Declaration of the underlying type
struct SDL_Texture;

namespace sdlxx::core {

/**
 * \brief A class for Texture-related exceptions.
 */
class TextureException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a texture in an efficient driver-specific way
 * \upstream SDL_Texture
 */
class Texture {
public:
  /**
   * \brief The scaling mode for a texture.
   * \upstream SDL_ScaleMode
   */
  enum class ScaleMode {
    NEAREST, /**< nearest pixel sampling */
    LINEAR,  /**< linear filtering */
    BEST     /**< anisotropic filtering */
  };

  /**
   * \brief The access pattern allowed for a texture.
   * \upstream SDL_TextureAccess
   */
  enum class Access {
    STATIC,    /**< Changes rarely, not lockable */
    STREAMING, /**< Changes frequently, lockable */
    TARGET     /**< Texture can be used as a render target */
  };

  /**
   * \brief The texture channel modulation used in Renderer::Copy().
   * \upstream SDL_TextureModulate
   */
  enum class Modulation {
    NONE = 0x00000000,  /**< No modulation */
    COLOR = 0x00000001, /**< srcC = srcC * color */
    ALPHA = 0x00000002  /**< srcA = srcA * alpha */
  };

  using Format = uint32_t;

  /**
   * \brief Create a texture for a rendering context.
   *
   * \param renderer   The renderer.
   * \param format     The format of the texture.
   * \param access     One of the enumerated values in ::Access.
   * \param dimensions The width and height of the texture in pixels.
   *
   * \throw TextureException if no rendering context was active, the format was unsupported,
   *                         or the width or height were out of range.
   *
   * \note The contents of the texture are not defined at creation.
   *
   * \upstream SDL_CreateTexture
   */
  Texture(Renderer& renderer, Dimensions dimensions, Format format = 0,
          Access access = Access::STATIC);

  /**
   * \brief Create a texture from an existing surface.
   *
   * \param renderer The renderer.
   * \param surface  The surface containing pixel data used to fill the texture.
   *
   * \throw TextureException on error.
   *
   * \note The surface is not modified or freed by this function.
   *
   * \upstream SDL_CreateTextureFromSurface
   */
  Texture(Renderer& renderer, const Surface& surface);

  /**
   * \brief Create a texture frow a raw pointer to SDL_Texture
   *
   * \param ptr The raw pointer to SDL_Texture
   */
  explicit Texture(SDL_Texture* ptr);

  struct Attributes {
    Dimensions dimensions;
    Format format;
    Access access;
  };

  /**
   * \brief Query the attributes of a texture
   *
   * \throw TextureException if the texture is not valid.
   *
   * \upstream SDL_QueryTexture
   */
  Attributes Query() const;

  // TODO: SDL_SetTextureColorMod, SDL_GetTextureColorMod, SDL_SetTextureAlphaMod,
  // SDL_GetTextureAlphaMod, SDL_SetTextureBlendMode, SDL_GetTextureBlendMode,
  // SDL_SetTextureScaleMode, SDL_GetTextureScaleMode, SDL_UpdateTexture, SDL_UpdateYUVTexture,
  // SDL_LockTexture, SDL_LockTextureToSurface, SDL_UnlockTexture, SDL_GL_BindTexture, SDL_GL_UnbindTexture

  // Friend declarations
  friend class Renderer;

protected:
  struct Deleter {
    void operator()(SDL_Texture* ptr) const;
  };

  std::unique_ptr<SDL_Texture, Deleter> texture_ptr;

  SDL_Renderer* GetRendererPtr(Renderer& renderer);
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_TEXTURE_H
