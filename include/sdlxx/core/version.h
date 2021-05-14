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
 * @file Version.h
 * @author Egor Makarenko
 * @brief Class that contains information about the version of the library
 */

#pragma once

#ifndef SDLXX_CORE_VERSION_H
#define SDLXX_CORE_VERSION_H

#include <cstdint>

namespace sdlxx::core {

/**
 * @brief Class that contains information about the version of the library
 */
class Version {
public:
  /**
   * @brief Major revision (increments with massive changes, additions, and
   * enhancements)
   */
  uint8_t major;

  /**
   * @brief Minor revision (increments with backwards-compatible changes to
   * the major revision)
   */
  uint8_t minor;

  /**
   * @brief Patchlevel (increments with fixes to the minor revision)
   */
  uint8_t patch;

  /**
   * @brief Construct a new Version object
   *
   * @param major Major revision
   * @param minor Minor revision
   * @param patch Patchlevel
   */
  Version(uint8_t major, uint8_t minor, uint8_t patch);

  // TODO: operator< and other meaningful operators
};

}  // namespace sdlxx::core

#endif  // SDLXX_CORE_VERSION_H
