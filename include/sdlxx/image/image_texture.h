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
 * \brief Header for the ImageTexture class that represents a texture loaded from an image file.
 */

#pragma once

#ifndef SDLXX_IMAGE_IMAGE_TEXTURE_H
#define SDLXX_IMAGE_IMAGE_TEXTURE_H

#include <string>

#include "sdlxx/core/renderer.h"
#include "sdlxx/core/texture.h"

namespace sdlxx::image {

using sdlxx::core::Exception;
using sdlxx::core::Renderer;
using sdlxx::core::Texture;

/**
 * \brief A class for ImageTexture-related exceptions.
 */
class ImageTextureException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that represents a texture loaded from an image file.
 */
class ImageTexture : public Texture {
public:
  explicit ImageTexture(Renderer& renderer, const std::string& path);
};

}  // namespace sdlxx::image

#endif  // SDLXX_IMAGE_IMAGE_TEXTURE_H
