#include <memory>
#include <system_error>

#include <SDL_ttf.h>
#include <sdlxx/core/version.h>
#include <sdlxx/ttf/SDLXX_ttf.h>

using namespace sdlxx::core;
using namespace sdlxx::ttf;

Version SDLXX_ttf::getCompiledSdlVersion() {
  SDL_version compiled;
  SDL_TTF_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version SDLXX_ttf::getLinkedSdlVersion() {
  std::unique_ptr<const SDL_version> linked(TTF_Linked_Version());
  return {linked->major, linked->minor, linked->patch};
}

bool SDLXX_ttf::initialized = false;

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
  initialized = true;
}

SDLXX_ttf::~SDLXX_ttf() {
  TTF_Quit();
  initialized = false;
}

bool SDLXX_ttf::wasInit() { return TTF_WasInit(); }
