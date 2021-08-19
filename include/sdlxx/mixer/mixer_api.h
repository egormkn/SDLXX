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
 * \brief Header for the TtfApi class that initializes the audio API.
 */

#ifndef SDLXX_MIXER_MIXER_API_H
#define SDLXX_MIXER_MIXER_API_H

#include "sdlxx/core/exception.h"
#include "sdlxx/core/version.h"
#include "sdlxx/utils/bitmask.h"

namespace sdlxx {

/**
 * \brief A class for MixerApi-related exceptions.
 */
class MixerApiException : public Exception {
  using Exception::Exception;
};

/**
 * \brief A class that initializes the audio API.
 */
class MixerApi {
public:
  /**
   * \brief An enumeration of library flags.
   * \upstream MIX_InitFlags
   */
  enum class Flag {
    FLAC = 0x00000001,
    MOD = 0x00000002,
    MP3 = 0x00000008,
    OGG = 0x00000010,
    MID = 0x00000020,
    OPUS = 0x00000040
  };

  /**
   * \brief Get the SDL_mixer version the library was compiled against.
   *
   * This is determined by what header the compiler used.
   *
   * \note If you dynamically linked the library, you might have a slightly newer or older version
   * at runtime. That version can be determined with GetLinkedSdlMixerVersion()
   *
   * \return Version The version of SDL_mixer the library was compiled against.
   *
   * \upstream SDL_MIXER_VERSION
   * \upstream SDL_MIXER_COMPILEDVERSION
   * \upstream SDL_MIXER_MAJOR_VERSION
   * \upstream SDL_MIXER_MINOR_VERSION
   * \upstream SDL_MIXER_PATCHLEVEL
   */
  static Version GetCompiledSdlMixerVersion();

  /**
   * \brief Get the SDL_mixer version the library was linked against.
   *
   * If you are linking to SDL_mixer dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * \return Version The version of SDL_mixer the library was linked against.
   *
   * \upstream Mix_Linked_Version
   */
  static Version GetLinkedSdlMixerVersion();

  /**
   * \brief Construct the MixerApi object that initializes the specified parts of the library.
   *
   * \param flags Parts of the library that should be initialized.
   *
   * \throw MixerApiException on failure.
   *
   * \upstream Mix_Init
   */
  explicit MixerApi(BitMask<Flag> flags);

  /**
   * \brief Destroy the MixerApi object cleaning up all initialized parts of the library.
   *
   * \upstream Mix_Quit
   */
  ~MixerApi();

  // TODO: initSubsystem/quitSubsystem/wasInit methods

  // Deleted copy constructor
  MixerApi(const MixerApi& other) = delete;

  // Deleted copy assignment operator
  MixerApi& operator=(const MixerApi& other) = delete;

  // Deleted move constructor
  MixerApi(MixerApi&& other) = delete;

  // Deleted move assignment operator
  MixerApi& operator=(MixerApi&& other) = delete;
};

}  // namespace sdlxx

ENABLE_BITMASK_OPERATORS(sdlxx::MixerApi::Flag);

#endif  // SDLXX_MIXER_MIXER_API_H
