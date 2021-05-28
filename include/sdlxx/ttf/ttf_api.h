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
 * \brief Header for the TtfApi class that initializes the fonts API.
 */

#pragma once

#ifndef SDLXX_TTF_TTF_API_H
#define SDLXX_TTF_TTF_API_H

#include "sdlxx/core/exception.h"
#include "sdlxx/core/version.h"

namespace sdlxx::ttf {

using sdlxx::core::Exception;
using sdlxx::core::Version;

/**
 * \brief A class for TtfApi-related exceptions.
 */
class TtfApiException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that initializes the fonts API.
 */
class TtfApi {
public:
  /**
   * \brief Get the SDL_ttf version the library was compiled against.
   *
   * This is determined by what header the compiler used.
   *
   * \note If you dynamically linked the library, you might have a slightly newer or older version
   * at runtime. That version can be determined with GetLinkedSdlTtfVersion().
   *
   * This function may be called safely at any time.
   *
   * \return Version The version of SDL_ttf the library was compiled against.
   *
   * \upstream SDL_TTF_MAJOR_VERSION
   * \upstream SDL_TTF_MINOR_VERSION
   * \upstream SDL_TTF_PATCHLEVEL
   * \upstream SDL_TTF_VERSION
   * \upstream SDL_TTF_COMPILEDVERSION
   */
  static Version GetCompiledSdlTtfVersion();

  /**
   * \brief Get the SDL_ttf version the library was linked against.
   *
   * If you are linking to SDL_ttf dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * This function may be called safely at any time.
   *
   * \return Version The version of SDL_ttf the library was linked against
   *
   * \upstream TTF_Linked_Version
   */
  static Version GetLinkedSdlTtfVersion();

  /**
   * \brief Construct the TtfApi object that initializes the fonts API.
   *
   * This object must be constructed before using other functions in this library, except WasInit().
   *
   * \note CoreApi does not have to be initialized before this call.
   *
   * \throw TtfApiException on failure.
   *
   * \upstream TTF_Init
   */
  explicit TtfApi();

  /**
   * \brief Destroy the TtfApi object cleaning up the fonts API.
   *
   * \upstream TTF_Quit
   */
  ~TtfApi();

  /**
   * \brief Query the initialization status of a fonts API.
   *
   * \return true if font API was initialized
   * \return false otherwise
   *
   * \upstream TTF_WasInit
   */
  static bool WasInit();

  /**
   * ZERO WIDTH NO-BREAKSPACE (Unicode byte order mark)
   *
   * \upstream UNICODE_BOM_NATIVE
   * \upstream UNICODE_BOM_SWAPPED
   */
  enum class BOM { NATIVE = 0xFEFF, SWAPPED = 0xFFFE };

  /**
   * This function tells the library whether UNICODE text is generally byteswapped.
   *
   * A UNICODE BOM character in a string will override this setting for the remainder of that
   * string.
   *
   * \param is_swapped If true then UNICODE data is byte swapped relative to the CPU's native
   *                   endianness. If false then do not swap UNICODE data, use the CPU's native
   *                   endianness.
   *
   * \upstream TTF_ByteSwappedUNICODE
   */
  static void SetByteSwappedUnicode(bool is_swapped);

  // Deleted copy constructor
  TtfApi(const TtfApi& other) = delete;

  // Deleted copy assignment operator
  TtfApi& operator=(const TtfApi& other) = delete;

  // Deleted move constructor
  TtfApi(TtfApi&& other) = delete;

  // Deleted move assignment operator
  TtfApi& operator=(TtfApi&& other) = delete;
};

}  // namespace sdlxx::ttf

#endif  // SDLXX_TTF_TTF_API_H
