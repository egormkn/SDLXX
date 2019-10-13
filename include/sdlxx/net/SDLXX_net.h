/**
 * @file SDLXX_net.h
 * @author Egor Makarenko
 * @brief Class that represents SDLXX object that initializes the network API
 */

#pragma once

#ifndef SDLXX_NET_H
#define SDLXX_NET_H

#include <cstdint>
#include <unordered_set>

namespace sdlxx::core {

// Forward declaration of Version class
class Version;

}  // namespace sdlxx::core

namespace sdlxx::net {

/**
 * @brief Class that represents SDLXX object that initializes the network API
 */
class SDLXX_net {
public:
  /**
   * @brief Get the SDL_net version the library was compiled against
   *
   * This is determined by what header the compiler used. Note that if you
   * dynamically linked the library, you might have a slightly newer or older
   * version at runtime. That version can be determined with
   * SDLXX_net::getLinkedSdlVersion()
   *
   * @return Version Version of SDL_net the library was compiled against
   */
  static sdlxx::core::Version getCompiledSdlVersion();

  /**
   * @brief Get the SDL_net version the library was linked against
   *
   * If you are linking to SDL_net dynamically, then it is possible that the
   * current version will be different than the version you compiled against.
   *
   * @return Version Version of SDL_net the library was linked against
   */
  static sdlxx::core::Version getLinkedSdlVersion();

  /**
   * @brief Construct the SDLXX_net object that initializes the network API
   *
   * This must be called before using other network-related functions.
   *
   * @note SDLXX_core must be initialized before this call.
   */
  SDLXX_net();

  /**
   * @brief Destroy the SDLXX_net object cleaning up the network API
   */
  ~SDLXX_net();

  /**
   * @brief Query the initialization status of a network API
   *
   * @return true if network API was initialized
   * @return false otherwise
   */
  static bool wasInit();

  // TODO: initSubsystem/quitSubsystem/wasInit methods

private:
  // Initialization status
  static bool initialized;

  // Deleted copy constructor
  SDLXX_net(const SDLXX_net& other) = delete;

  // Deleted copy assignment operator
  SDLXX_net& operator=(const SDLXX_net& other) = delete;

  // Deleted move constructor
  SDLXX_net(SDLXX_net&& other) = delete;

  // Deleted move assignment operator
  SDLXX_net& operator=(SDLXX_net&& other) = delete;
};

}  // namespace sdlxx::net

#endif  // SDLXX_NET_H
