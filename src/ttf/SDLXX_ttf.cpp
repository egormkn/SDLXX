#include <system_error>

#include <SDL_ttf.h>
#include <sdlxx/ttf/SDLXX_ttf.h>

using namespace sdlxx::core;
using namespace sdlxx::ttf;

SDLXX_ttf::Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
    : SDLXX::Version::Version(major, minor, patch) {}

SDLXX_ttf::Version SDLXX_ttf::Version::getCompiledSdlTtfVersion() {
  SDL_version compiled;
  SDL_TTF_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

SDLXX_ttf::Version SDLXX_ttf::Version::getLinkedSdlTtfVersion() {
  const SDL_version* linked = TTF_Linked_Version();
  return {linked->major, linked->minor, linked->patch};
}

SDLXX_ttf::SDLXX_ttf() {
  if (SDLXX_ttf::wasInit()) {
    throw std::runtime_error("SDLXX_ttf was already initialized");
  }
  int return_code = TTF_Init();
  if (return_code != 0) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize SDLXX_ttf: " + std::string(TTF_GetError()));
  }
}

bool SDLXX_ttf::wasInit() { return TTF_WasInit(); }

SDLXX_ttf::~SDLXX_ttf() { TTF_Quit(); }
