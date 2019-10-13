/**
 * @file SDLXX_ttf.h
 * @author Egor Makarenko
 * @brief Class that represents SDLXX object that initializes the font API
 */

#pragma once

#ifndef SDLXX_TTF_H
#define SDLXX_TTF_H

#include <cstdint>

namespace sdlxx::core {

// Forward declaration of Version class
class Version;

}  // namespace sdlxx::core

namespace sdlxx::ttf {

/**
 * @brief Class that represents SDLXX object that initializes the font API
 */
class SDLXX_ttf {
public:
  /**
   * @brief Get the SDL_ttf version the library was compiled against
   *
   * This is determined by what header the compiler used. Note that if you
   * dynamically linked the library, you might have a slightly newer or older
   * version at runtime. That version can be determined with
   * SDLXX_ttf::getLinkedSdlVersion()
   *
   * @return Version Version of SDL_ttf the library was compiled against
   */
  static sdlxx::core::Version getCompiledSdlVersion();

  /**
   * @brief Get the SDL_ttf version the library was linked against
   *
   * If you are linking to SDL_ttf dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * @return Version Version of SDL_ttf the library was linked against
   */
  static sdlxx::core::Version getLinkedSdlVersion();

  /**
   * @brief Construct the SDLXX_ttf object that initializes the font API
   *
   * This must be called before using other font-related functions.
   *
   * @note SDLXX_core does not have to be initialized before this call.
   */
  SDLXX_ttf();

  /**
   * @brief Destroy the SDLXX_net object cleaning up the font API
   */
  ~SDLXX_ttf();

  /**
   * @brief Query the initilization status of a font API
   *
   * @return true if font API was initialized
   * @return false otherwise
   */
  static bool wasInit();

  // TODO: initSubsystem/quitSubsystem/wasInit methods

private:
  // Initialization status
  static bool initialized;

  // Deleted copy constructor
  SDLXX_ttf(const SDLXX_ttf& other) = delete;

  // Deleted copy assignment operator
  SDLXX_ttf& operator=(const SDLXX_ttf& other) = delete;

  // Deleted move constructor
  SDLXX_ttf(SDLXX_ttf&& other) = delete;

  // Deleted move assignment operator
  SDLXX_ttf& operator=(SDLXX_ttf&& other) = delete;
};

}  // namespace sdlxx::ttf

#endif  // SDLXX_TTF_H
