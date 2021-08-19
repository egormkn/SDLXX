#include <memory>
#include <numeric>
#include <string>
#include <system_error>
#include <type_traits>

#include <SDL_net.h>
#include <sdlxx/core/version.h>
#include <sdlxx/net/net_api.h>

using namespace sdlxx::core;
using namespace sdlxx::net;

Version net_api::getCompiledSdlVersion() {
  SDL_version compiled;
  SDL_NET_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version net_api::getLinkedSdlVersion() {
  std::unique_ptr<const SDL_version> linked(SDLNet_Linked_Version());
  return {linked->major, linked->minor, linked->patch};
}

bool net_api::initialized = false;

net_api::net_api() {
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

net_api::~net_api() {
  SDLNet_Quit();
  initialized = false;
}

bool net_api::wasInit() { return initialized; }
