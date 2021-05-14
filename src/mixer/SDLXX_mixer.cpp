#include <memory>
#include <numeric>
#include <system_error>
#include <type_traits>

#include <SDL_mixer.h>
#include <sdlxx/core/version.h>
#include <sdlxx/mixer/SDLXX_mixer.h>

using namespace sdlxx::core;
using namespace sdlxx::mixer;

// Convert options into bit mask
template <typename Mask = uint32_t, typename Flag>
Mask GetFlagsMask(const std::unordered_set<Flag>& flags) {
  return std::accumulate(
      flags.begin(), flags.end(), 0, [](Mask flags, const Flag& flag) {
        return flags | static_cast<std::underlying_type_t<Flag>>(flag);
      });
}

Version SDLXX_mixer::getCompiledSdlVersion() {
  SDL_version compiled;
  SDL_MIXER_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version SDLXX_mixer::getLinkedSdlVersion() {
  std::unique_ptr<const SDL_version> linked(Mix_Linked_Version());
  return {linked->major, linked->minor, linked->patch};
}

bool SDLXX_mixer::initialized = false;

SDLXX_mixer::SDLXX_mixer(const std::unordered_set<Subsystem>& subsystems) {
  if (initialized) {
    throw std::runtime_error("SDLXX_mixer was already initialized");
  }
  int flags = GetFlagsMask<int>(subsystems);
  int return_code = Mix_Init(flags);
  if (return_code != flags) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize SDL_mixer: " + std::string(Mix_GetError()));
  }
  initialized = true;
}

SDLXX_mixer::~SDLXX_mixer() {
  Mix_Quit();
  initialized = false;
}
