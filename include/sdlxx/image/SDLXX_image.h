/**
 * @file SDLXX_image.h
 * @author Egor Makarenko
 * @brief Class that represents SDLXX object that initializes the image API
 */

#pragma once

#ifndef SDLXX_IMAGE_H
#define SDLXX_IMAGE_H

#include <cstdint>
#include <unordered_set>

namespace sdlxx::core {

// Forward declaration of Version class
class Version;

}  // namespace sdlxx::core

namespace sdlxx::image {

/**
 * @brief Class that represents SDLXX object that initializes the image API
 */
class SDLXX_image {
public:
  /**
   * @brief Get the SDL_image version the library was compiled against
   *
   * This is determined by what header the compiler used. Note that if you
   * dynamically linked the library, you might have a slightly newer or older
   * version at runtime. That version can be determined with
   * SDLXX_image::getLinkedSdlVersion()
   *
   * @return Version Version of SDL_image the library was compiled against
   */
  static sdlxx::core::Version getCompiledSdlVersion();

  /**
   * @brief Get the SDL_image version the library was linked against
   *
   * If you are linking to SDL_image dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * @return Version Version of SDL_image the library was linked against
   */
  static sdlxx::core::Version getLinkedSdlVersion();

  /**
   * @brief An enumeration of library subsystems
   */
  enum class Subsystem : int32_t {
    JPG = 0x00000001,
    PNG = 0x00000002,
    TIF = 0x00000004,
    WEBP = 0x00000008
  };

  /**
   * @brief Construct the SDLXX_image object that initializes the specified
   *        Subsystems of the library
   *
   * @param subsystems Subsystems that should be initialized
   */
  explicit SDLXX_image(const std::unordered_set<Subsystem>& subsystems = {});

  /**
   * @brief Destroy the SDLXX_image object cleaning up all initialized
   * subsystems.
   *
   * @note You should call this function upon all exit conditions.
   */
  ~SDLXX_image();

  // TODO: initSubsystem/quitSubsystem/wasInit methods

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
