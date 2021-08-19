/**
 * @file SDLXX_mixer.h
 * @author Egor Makarenko
 * @brief Class that represents SDLXX object that initializes the audio API
 */

#pragma once

#ifndef SDLXX_MIXER_H
#define SDLXX_MIXER_H

#include <cstdint>
#include <unordered_set>

namespace sdlxx::core {

// Forward declaration of Version class
class Version;

}  // namespace sdlxx::core

namespace sdlxx::mixer {

/**
 * @brief Class that represents SDLXX object that initializes the audio API
 */
class mixer_api {
public:
  /**
   * @brief Get the SDL_mixer version the library was compiled against
   *
   * This is determined by what header the compiler used. Note that if you
   * dynamically linked the library, you might have a slightly newer or older
   * version at runtime. That version can be determined with
   * SDLXX_mixer::getLinkedSdlVersion()
   *
   * @return Version Version of SDL_mixer the library was compiled against
   */
  static sdlxx::core::Version getCompiledSdlVersion();

  /**
   * @brief Get the SDL_mixer version the library was linked against
   *
   * If you are linking to SDL_mixer dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * @return Version Version of SDL_mixer the library was linked against
   */
  static sdlxx::core::Version getLinkedSdlVersion();

  /**
   * @brief An enumeration of library subsystems
   */
  enum class Subsystem : int32_t {
    FLAC = 0x00000001,
    MOD = 0x00000002,
    MP3 = 0x00000008,
    OGG = 0x00000010,
    MID = 0x00000020,
    OPUS = 0x00000040
  };

  /**
   * @brief Construct a new SDLXX_mixer object that initializes the specified
   *        Subsystems of the library
   *
   * @param subsystems Subsystems that should be initialized
   */
  explicit mixer_api(const std::unordered_set<Subsystem>& subsystems = {});

  /**
   * @brief Destroy the SDLXX_mixer object cleaning up all initialized
   * subsystems.
   *
   * @note You should call this function upon all exit conditions.
   */
  ~mixer_api();

  // TODO: initSubsystem/quitSubsystem/wasInit methods

private:
  // Initialization status
  static bool initialized;

  // Deleted copy constructor
  mixer_api(const mixer_api& other) = delete;

  // Deleted copy assignment operator
  mixer_api& operator=(const mixer_api& other) = delete;

  // Deleted move constructor
  mixer_api(mixer_api&& other) = delete;

  // Deleted move assignment operator
  mixer_api& operator=(mixer_api&& other) = delete;
};

}  // namespace sdlxx::mixer

#endif  // SDLXX_MIXER_H
