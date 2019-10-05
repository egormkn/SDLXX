/**
 * @file SDLXX_ttf.h
 * @author Egor Makarenko
 * @brief Class that represents SDLXX ttf object that initializes the font API
 */

#pragma once

#ifndef SDLXX_TTF_H
#define SDLXX_TTF_H

#include <sdlxx/core/SDLXX_core.h>

namespace sdlxx::ttf {

/**
 * @brief Class that represents SDLXX ttf object that initializes the font API
 */
class SDLXX_ttf {
public:
  /**
   * @copydoc sdlxx::core::SDLXX::Version
   */
  class Version : public sdlxx::core::SDLXX::Version {
    /**
     * @copydoc sdlxx::core::SDLXX::Version::Version
     */
    Version(uint8_t major, uint8_t minor, uint8_t patch);

    /**
     * @brief Get the SDL_ttf version the SDLXX library was compiled against
     *
     * This is determined by what header the compiler used. Note that if you
     * dynamically linked the library, you might have a slightly newer or older
     * version at runtime. That version can be determined with
     * SDLXX_ttf::Version::getLinkedSdlTtfVersion()
     *
     * @return Version Version of SDL_ttf the library was compiled against
     */
    static Version getCompiledSdlTtfVersion();

    /**
     * @brief Get the SDL_ttf version the SDLXX library was linked against
     *
     * If you are linking to SDL_ttf dynamically, then it is possible that the
     * current version will be different than the version you compiled against.
     *
     * @return Version Version of SDL_ttf the library was linked against
     */
    static Version getLinkedSdlTtfVersion();
  };

  /**
   * @brief Construct an SDLXX_ttf object and initialize the truetype font API
   *
   * This must be called before using other TTF-related functions, except
   * SDLXX_ttf::wasInit. SDLXX does not have to be initialized before this call
   */
  SDLXX_ttf();

  /**
   * @brief Query the initilization status of the truetype font API
   *
   * @return true if truetype font API was initialized
   * @return false otherwise
   */
  static bool wasInit();

  /**
   * @brief Destroy the sdlxx ttf object and clean up the truetype font API
   */
  ~SDLXX_ttf();

private:
  // Deleted copy constructor
  // This class is not copyable
  SDLXX_ttf(const SDLXX_ttf& other) = delete;

  // Deleted assignment operator
  // This class is not copyable
  SDLXX_ttf& operator=(const SDLXX_ttf& other) = delete;

  // Deleted move constructor
  // This class is not movable
  SDLXX_ttf(SDLXX_ttf&& other) = delete;

  // Deleted move assignment operator
  // This class is not movable
  SDLXX_ttf& operator=(SDLXX_ttf&& other) = delete;
};
}  // namespace sdlxx::ttf

#endif  // SDLXX_TTF_H
