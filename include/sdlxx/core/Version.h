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
