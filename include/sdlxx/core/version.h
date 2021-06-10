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
 * \brief Header for the Version structure that contains information about the library version.
 */

#ifndef SDLXX_CORE_VERSION_H
#define SDLXX_CORE_VERSION_H

#include <cstdint>

namespace sdlxx {

/**
 * \brief A structure that contains information about the library version.
 *
 * Represents the library's version as three levels:
 * - major revision (increments with massive changes, additions, and enhancements),
 * - minor revision (increments with backwards-compatible changes to the major revision),
 * - patchlevel (increments with fixes to the minor revision).
 */
struct Version {
  uint8_t major;  ///< Major revision (increments with massive changes and enhancements).
  uint8_t minor;  ///< Minor revision (increments with backwards-compatible changes).
  uint8_t patch;  ///< Patchlevel (increments with fixes to the minor revision).

  /**
   * \brief Construct a new Version object.
   *
   * \param major Major revision.
   * \param minor Minor revision.
   * \param patch Patchlevel.
   *
   * \upstream SDL_version
   */
  Version(uint8_t major, uint8_t minor, uint8_t patch);

  /**
   * \brief Test whether this version is less than other.
   *
   * \param other Version object to compare to.
   * \return true if the version is less than other, false otherwise.
   *
   * \upstream SDL_VERSIONNUM
   * \upstream SDL_VERSION_ATLEAST
   */
  bool operator<(const Version& other) const;
  bool operator>(Version& other) const;
  bool operator<=(Version& other) const;
  bool operator>=(Version& other) const;

  /**
   * \brief Test whether this version is equal to other.
   *
   * \param other Version object to compare to.
   * \return true if the version is equal to other, false otherwise.
   *
   * \upstream SDL_VERSIONNUM
   * \upstream SDL_VERSION_ATLEAST
   */
  bool operator==(const Version& other) const;
  bool operator!=(const Version& other) const;
};

}  // namespace sdlxx

#endif  // SDLXX_CORE_VERSION_H
