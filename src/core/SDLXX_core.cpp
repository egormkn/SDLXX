#include <numeric>
#include <sstream>
#include <system_error>
#include <unordered_set>

#include <SDL.h>
#include <SDL_hints.h>
#include <SDL_version.h>
#include <sdlxx/core/SDLXX_core.h>

using namespace sdlxx::core;

bool SDLXX::initialized = false;

SDLXX::Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
    : major_version(major), minor_version(minor), patch_version(patch) {}

SDLXX::Version SDLXX::Version::getCompiledSdlVersion() {
  SDL_version compiled;
  SDL_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

SDLXX::Version SDLXX::Version::getLinkedSdlVersion() {
  SDL_version linked;
  SDL_GetVersion(&linked);
  return {linked.major, linked.minor, linked.patch};
}

SDLXX::SDLXX(const std::unordered_set<Subsystem>& subsystems) {
  if (initialized) {
    throw std::runtime_error("SDLXX is already initialized");
  }
  Uint32 flags =
      std::accumulate(subsystems.begin(), subsystems.end(), 0,
                      [](Uint32 flags, const Subsystem& subsystem) {
                        return flags | static_cast<uint32_t>(subsystem);
                      });
  int return_code = SDL_Init(flags);
  if (return_code != 0) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize SDL: " + std::string(SDL_GetError()));
  }
  initialized = true;
}

SDLXX::~SDLXX() {
  SDL_Quit();
  initialized = false;
}

void SDLXX::initSubsystem(const Subsystem& subsystem) {
  Uint32 flag = static_cast<uint32_t>(subsystem);
  int return_code = SDL_InitSubSystem(flag);
  if (return_code != 0) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize subsystem: " + std::string(SDL_GetError()));
  }
}

void SDLXX::initSubsystem(const std::unordered_set<Subsystem>& subsystems) {
  Uint32 flags =
      std::accumulate(subsystems.begin(), subsystems.end(), 0,
                      [](Uint32 flags, const Subsystem& subsystem) {
                        return flags | static_cast<uint32_t>(subsystem);
                      });
  int return_code = SDL_InitSubSystem(flags);
  if (return_code != 0) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to initialize subsystems: " + std::string(SDL_GetError()));
  }
}

void SDLXX::quitSubsystem(const Subsystem& subsystem) {
  Uint32 flag = static_cast<uint32_t>(subsystem);
  SDL_QuitSubSystem(flag);
}

void SDLXX::quitSubsystem(const std::unordered_set<Subsystem>& subsystems) {
  Uint32 flags =
      std::accumulate(subsystems.begin(), subsystems.end(), 0,
                      [](Uint32 flags, const Subsystem& subsystem) {
                        return flags | static_cast<uint32_t>(subsystem);
                      });
  SDL_QuitSubSystem(flags);
}

std::unordered_set<SDLXX::Subsystem> SDLXX::wasInit(
    const std::unordered_set<Subsystem>& subsystems) const {
  Uint32 flags =
      std::accumulate(subsystems.begin(), subsystems.end(), 0,
                      [](Uint32 flags, const Subsystem& subsystem) {
                        return flags | static_cast<uint32_t>(subsystem);
                      });
  Uint32 current = SDL_WasInit(flags);
  std::unordered_set<Subsystem> result;
  for (const Subsystem& s :
       {Subsystem::TIMER, Subsystem::AUDIO, Subsystem::VIDEO,
        Subsystem::JOYSTICK, Subsystem::HAPTIC, Subsystem::GAMECONTROLLER,
        Subsystem::EVENTS, Subsystem::SENSOR}) {
    if (static_cast<uint32_t>(s) & current) {
      result.insert(s);
    }
  }
  return result;
}

bool SDLXX::wasInit(const Subsystem& subsystem) const {
  Uint32 flag = static_cast<uint32_t>(subsystem);
  return SDL_WasInit(flag) != 0;
}

bool SDLXX::setHint(const std::string& name, const std::string& value,
                    const HintPriority& priority) {
  return SDL_SetHintWithPriority(name.c_str(), value.c_str(),
                                 static_cast<SDL_HintPriority>(priority));
}

std::optional<std::string> SDLXX::getHint(const std::string& name) {
  const char* value = SDL_GetHint(name.c_str());
  if (!value) {
    return std::nullopt;
  }
  return {std::string(value)};
}

std::optional<bool> SDLXX::getHintBoolean(const std::string& name) {
  const char* value = SDL_GetHint(name.c_str());
  if (!value || !*value) {
    return std::nullopt;
  }
  return {*value != '0' && SDL_strcasecmp(value, "false") != 0};
}

void SDLXX::clearHints() { SDL_ClearHints(); }
