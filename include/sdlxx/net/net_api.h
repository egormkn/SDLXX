/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)

  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the NetApi class that initializes the network API.
 */

#ifndef SDLXX_NET_NET_API_H
#define SDLXX_NET_NET_API_H

#include <cstdint>

#include "sdlxx/core/exception.h"
#include "sdlxx/core/version.h"
#include "sdlxx/utils/bitmask.h"

namespace sdlxx {

/**
 * \brief A class for NetApi-related exceptions.
 */
class NetApiException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that initializes the network API.
 */
class NetApi {
public:
  /**
   * \brief Get the SDL_net version the library was compiled against.
   *
   * This is determined by what header the compiler used.
   *
   * \note If you dynamically linked the library, you might have a slightly newer or older version
   * at runtime. That version can be determined with GetLinkedSdlNetVersion().
   *
   * \return Version The version of SDL_net the library was compiled against.
   *
   * \upstream SDL_NET_VERSION
   * \upstream SDL_NET_MAJOR_VERSION
   * \upstream SDL_NET_MINOR_VERSION
   * \upstream SDL_NET_PATCHLEVEL
   */
  static Version GetCompiledSdlNetVersion();

  /**
   * \brief Get the SDL_net version the library was linked against.
   *
   * If you are linking to SDL_net dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * \return Version The version of SDL_net the library was linked against.
   *
   * \upstream SDLNet_Linked_Version
   */
  static Version GetLinkedSdlNetVersion();

  /**
   * \brief Construct the NetApi object that initializes the network API.
   *
   * This must be called before using other network-related functions.
   *
   * \note CoreApi must be initialized before this call.
   *
   * \throw NetApiException on failure.
   *
   * \upstream SDLNet_Init
   */
  explicit NetApi();

  /**
   * \brief Destroy the NetApi object cleaning up the network API.
   */
  ~NetApi();

  // TODO: initSubsystem/quitSubsystem/wasInit methods

  // Deleted copy constructor
  NetApi(const NetApi& other) = delete;

  // Deleted copy assignment operator
  NetApi& operator=(const NetApi& other) = delete;

  // Deleted move constructor
  NetApi(NetApi&& other) = delete;

  // Deleted move assignment operator
  NetApi& operator=(NetApi&& other) = delete;
};

}  // namespace sdlxx

#endif  // SDLXX_NET_NET_API_H
