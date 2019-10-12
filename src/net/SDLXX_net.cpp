#include <system_error>
#include <string>

#include <SDL_net.h>
#include <sdlxx/net/SDLXX_net.h>

using namespace sdlxx::core;
using namespace sdlxx::net;

bool SDLXX_net::initialized = false;

SDLXX_net::Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
    : SDLXX_core::Version::Version(major, minor, patch) {}

SDLXX_net::Version SDLXX_net::Version::getCompiledSdlNetVersion() {
  SDL_version compiled;
  SDL_NET_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

SDLXX_net::Version SDLXX_net::Version::getLinkedSdlNetVersion() {
  const SDL_version* linked = SDLNet_Linked_Version();
  return {linked->major, linked->minor, linked->patch};
}

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

bool SDLXX_net::wasInit() { return initialized; }

SDLXX_net::~SDLXX_net() {
  SDLNet_Quit();
  initialized = false;
}
