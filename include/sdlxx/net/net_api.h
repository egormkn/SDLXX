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
class net_api {
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
  net_api();

  /**
   * @brief Destroy the SDLXX_net object cleaning up the network API
   */
  ~net_api();

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
  net_api(const net_api& other) = delete;

  // Deleted copy assignment operator
  net_api& operator=(const net_api& other) = delete;

  // Deleted move constructor
  net_api(net_api&& other) = delete;

  // Deleted move assignment operator
  net_api& operator=(net_api&& other) = delete;
};

}  // namespace sdlxx::net

#endif  // SDLXX_NET_H
