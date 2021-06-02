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
 * \brief Header for the ImageApi class that initializes the image API.
 */

#ifndef SDLXX_IMAGE_IMAGE_API_H
#define SDLXX_IMAGE_IMAGE_API_H

#include <cstdint>

#include "sdlxx/core/exception.h"
#include "sdlxx/core/utils/bitmask.h"
#include "sdlxx/core/version.h"

namespace sdlxx::image {

using sdlxx::core::BitMask;

/**
 * \brief A class for ImageApi-related exceptions.
 */
class ImageApiException : public sdlxx::core::Exception {
  using Exception::Exception;
};

/**
 * \brief A class that initializes the image API.
 */
class ImageApi {
public:
  /**
   * \brief An enumeration of library flags.
   * \upstream IMG_InitFlags
   */
  enum class Flag : uint32_t {
    JPG = 0x00000001U,
    PNG = 0x00000002U,
    TIF = 0x00000004U,
    WEBP = 0x00000008U
  };

  /**
   * \brief Get the SDL_image version the library was compiled against.
   *
   * This is determined by what header the compiler used.
   *
   * \note If you dynamically linked the library, you might have a slightly newer or older version
   * at runtime. That version can be determined with GetLinkedSdlImageVersion().
   *
   * This function may be called safely at any time.
   *
   * \return Version The version of SDL_image the library was compiled against.
   *
   * \upstream SDL_IMAGE_VERSION
   * \upstream SDL_IMAGE_COMPILEDVERSION
   * \upstream SDL_IMAGE_MAJOR_VERSION
   * \upstream SDL_IMAGE_MINOR_VERSION
   * \upstream SDL_IMAGE_PATCHLEVEL
   */
  static sdlxx::core::Version GetCompiledSdlImageVersion();

  /**
   * \brief Get the SDL_image version the library was linked against.
   *
   * If you are linking to SDL_image dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * This function may be called safely at any time.
   *
   * \return Version The version of SDL_image the library was linked against.
   *
   * \upstream IMG_Linked_Version
   */
  static sdlxx::core::Version GetLinkedSdlImageVersion();

  /**
   * \brief Construct the ImageApi object that initializes the specified parts of the library.
   *
   * \param flags Parts of the library that should be initialized.
   *
   * \throw ImageApiException on failure.
   *
   * \upstream IMG_Init
   */
  explicit ImageApi(BitMask<Flag> flags);

  /**
   * \brief Destroy the ImageApi object cleaning up all initialized parts of the library.
   *
   * \upstream IMG_Quit
   */
  ~ImageApi();

  /**
   * \brief Get a set of initialized library parts.
   *
   * \return Flags A set of initialized library parts.
   *
   * \upstream IMG_Init
   */
  static BitMask<Flag> WasInit();

  /**
   * \brief Check whether a specified library part has been initialized.
   *
   * \return true if a specified library part has been initialized.
   * \return false otherwise.
   *
   * \upstream IMG_Init
   */
  static bool WasInit(Flag flag);

  // TODO: IMG_isXXX

  // Deleted copy constructor
  ImageApi(const ImageApi& other) = delete;

  // Deleted copy assignment operator
  ImageApi& operator=(const ImageApi& other) = delete;

  // Deleted move constructor
  ImageApi(ImageApi&& other) = delete;

  // Deleted move assignment operator
  ImageApi& operator=(ImageApi&& other) = delete;
};

}  // namespace sdlxx::image

ENABLE_BITMASK_OPERATORS(sdlxx::image::ImageApi::Flag);

#endif  // SDLXX_IMAGE_IMAGE_API_H
