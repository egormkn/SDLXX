/**
 * @file SDLXX_image.h
 * @author Egor Makarenko
 * @brief Class that represents SDLXX object that initializes the image API
 */

#pragma once

#ifndef SDLXX_IMAGE_H
#define SDLXX_IMAGE_H

#include <sdlxx/core/SDLXX_core.h>

namespace sdlxx::image {

/**
 * @brief Class that represents SDLXX object that initializes the image API
 */
class SDLXX_image {
public:
  /**
   * @copydoc sdlxx::core::SDLXX_core::Version
   */
  class Version : public sdlxx::core::SDLXX_core::Version {
    /**
     * @copydoc sdlxx::core::SDLXX_core::Version::Version
     */
    Version(uint8_t major, uint8_t minor, uint8_t patch);

    /**
     * @brief Get the SDL_image version the SDLXX library was compiled against
     *
     * This is determined by what header the compiler used. Note that if you
     * dynamically linked the library, you might have a slightly newer or older
     * version at runtime. That version can be determined with
     * SDLXX_image::Version::getLinkedSdlImageVersion()
     *
     * @return Version Version of SDL_image the library was compiled against
     */
    static Version getCompiledSdlImageVersion();

    /**
     * @brief Get the SDL_image version the SDLXX library was linked against
     *
     * If you are linking to SDL_image dynamically, then it is possible that the
     * current version will be different than the version you compiled against.
     *
     * @return Version Version of SDL_image the library was linked against
     */
    static Version getLinkedSdlImageVersion();
  };

  /**
   * @brief An enumeration of library subsystems
   */
  enum class Subsystem : int32_t {
    JPG = 0x00000001,
    PNG = 0x00000002,
    TIF = 0x00000004,
    WEBP = 0x00000008
  };

  // Init SDL_image
  explicit SDLXX_image(const std::unordered_set<Subsystem>& subsystems = {});

  // Quit SDL_image
  ~SDLXX_image();

  // TODO: wasInit and other functions

private:
  // Initialization status
  static bool initialized;

  // Deleted copy constructor
  SDLXX_image(const SDLXX_image& other) = delete;

  // Deleted copy assignment operator
  SDLXX_image& operator=(const SDLXX_image& other) = delete;

  // Deleted move constructor
  SDLXX_image(SDLXX_image&& other) = delete;

  // Deleted move assignment operator
  SDLXX_image& operator=(SDLXX_image&& other) = delete;
};

}  // namespace sdlxx::image

#endif  // SDLXX_IMAGE_H
