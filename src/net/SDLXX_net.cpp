#include <memory>
#include <numeric>
#include <string>
#include <system_error>
#include <type_traits>

#include <SDL_net.h>
#include <sdlxx/core/Version.h>
#include <sdlxx/net/SDLXX_net.h>

using namespace sdlxx::core;
using namespace sdlxx::net;

Version SDLXX_net::getCompiledSdlVersion() {
  SDL_version compiled;
  SDL_NET_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version SDLXX_net::getLinkedSdlVersion() {
  std::unique_ptr<const SDL_version> linked(SDLNet_Linked_Version());
  return {linked->major, linked->minor, linked->patch};
}

bool SDLXX_net::initialized = false;

SDLXX_net::SDLXX_net() {
  if (initialized) {
    throw std::runtime_error("SDLXX_net was already initialized");
  }
  int return_code = SDLNet_Init();
  if (return_code != 0) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize SDLXX_net: " + std::string(SDLNet_GetError()));
  }
  initialized = true;
}

SDLXX_net::~SDLXX_net() {
  SDLNet_Quit();
  initialized = false;
}

bool SDLXX_net::wasInit() { return initialized; }
