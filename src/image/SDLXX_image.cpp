#include <memory>
#include <numeric>
#include <system_error>
#include <type_traits>

#include <SDL_image.h>
#include <sdlxx/core/version.h>
#include <sdlxx/image/SDLXX_image.h>

using namespace sdlxx::core;
using namespace sdlxx::image;

// Convert options into bit mask
template <typename Mask = uint32_t, typename Flag>
Mask GetFlagsMask(const std::unordered_set<Flag>& flags) {
  return std::accumulate(
      flags.begin(), flags.end(), 0, [](Mask flags, const Flag& flag) {
        return flags | static_cast<std::underlying_type_t<Flag>>(flag);
      });
}

Version SDLXX_image::getCompiledSdlVersion() {
  SDL_version compiled;
  SDL_IMAGE_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version SDLXX_image::getLinkedSdlVersion() {
  std::unique_ptr<const SDL_version> linked(IMG_Linked_Version());
  return {linked->major, linked->minor, linked->patch};
}

bool SDLXX_image::initialized = false;

SDLXX_image::SDLXX_image(const std::unordered_set<Subsystem>& subsystems) {
  if (initialized) {
    throw std::runtime_error("SDLXX_image was already initialized");
  }
  int flags = GetFlagsMask<int>(subsystems);
  int return_code = IMG_Init(flags);
  if (return_code != flags) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize SDL_image: " + std::string(IMG_GetError()));
  }
  initialized = true;
}

SDLXX_image::~SDLXX_image() {
  IMG_Quit();
  initialized = false;
}
