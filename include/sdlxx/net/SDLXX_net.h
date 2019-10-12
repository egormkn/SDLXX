/**
 * @file SDLXX_net.h
 * @author Egor Makarenko
 * @brief Class that initializes the network API
 */

#pragma once

#ifndef SDLXX_NET_H
#define SDLXX_NET_H

#include <sdlxx/core/SDLXX_core.h>

namespace sdlxx::net {

/**
 * @brief Class that initializes the network API
 */
class SDLXX_net {
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
     * @brief Get the SDL_net version the SDLXX library was compiled against
     *
     * This is determined by what header the compiler used. Note that if you
     * dynamically linked the library, you might have a slightly newer or older
     * version at runtime. That version can be determined with
     * SDLXX_net::Version::getLinkedSdlNetVersion()
     *
     * @return Version Version of SDL_net the library was compiled against
     */
    static Version getCompiledSdlNetVersion();

    /**
     * @brief Get the SDL_net version the SDLXX library was linked against
     *
     * If you are linking to SDL_net dynamically, then it is possible that the
     * current version will be different than the version you compiled against.
     *
     * @return Version Version of SDL_net the library was linked against
     */
    static Version getLinkedSdlNetVersion();
  };

  /**
   * @brief Construct the SDLXX_net object and initialize the network API
   *
   * This must be called before using other network-related functions.
   * SDLXX must be initialized before this call.
   */
  SDLXX_net();

  /**
   * @brief Query the initialization status of a network API
   *
   * @return true if network API was initialized
   * @return false otherwise
   */
  static bool wasInit();

  /**
   * @brief Destroy the SDLXX_net object and clean up the network API
   */
  ~SDLXX_net();

private:
  // Initialization status
  static bool initialized;

  // Deleted copy constructor
  // This class is not copyable
  SDLXX_net(const SDLXX_net& other) = delete;

  // Deleted assignment operator
  // This class is not copyable
  SDLXX_net& operator=(const SDLXX_net& other) = delete;

  // Deleted move constructor
  // This class is not movable
  SDLXX_net(SDLXX_net&& other) = delete;

  // Deleted move assignment operator
  // This class is not movable
  SDLXX_net& operator=(SDLXX_net&& other) = delete;
};
}  // namespace sdlxx::net

#endif  // SDLXX_NET_H
