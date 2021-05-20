#include "sdlxx/core/core_api.h"

#include <SDL.h>
#include <SDL_hints.h>

using namespace sdlxx::core;

static_assert(static_cast<uint32_t>(CoreApi::Flag::TIMER) == SDL_INIT_TIMER);
static_assert(static_cast<uint32_t>(CoreApi::Flag::AUDIO) == SDL_INIT_AUDIO);
static_assert(static_cast<uint32_t>(CoreApi::Flag::VIDEO) == SDL_INIT_VIDEO);
static_assert(static_cast<uint32_t>(CoreApi::Flag::JOYSTICK) == SDL_INIT_JOYSTICK);
static_assert(static_cast<uint32_t>(CoreApi::Flag::HAPTIC) == SDL_INIT_HAPTIC);
static_assert(static_cast<uint32_t>(CoreApi::Flag::GAMECONTROLLER) == SDL_INIT_GAMECONTROLLER);
static_assert(static_cast<uint32_t>(CoreApi::Flag::EVENTS) == SDL_INIT_EVENTS);
static_assert(static_cast<uint32_t>(CoreApi::Flag::SENSOR) == SDL_INIT_SENSOR);
static_assert(static_cast<uint32_t>(CoreApi::Flag::NOPARACHUTE) == SDL_INIT_NOPARACHUTE);
static_assert(static_cast<uint32_t>(CoreApi::Flag::EVERYTHING) == SDL_INIT_EVERYTHING);

static_assert(static_cast<SDL_HintPriority>(CoreApi::HintPriority::DEFAULT) == SDL_HINT_DEFAULT);
static_assert(static_cast<SDL_HintPriority>(CoreApi::HintPriority::NORMAL) == SDL_HINT_NORMAL);
static_assert(static_cast<SDL_HintPriority>(CoreApi::HintPriority::OVERRIDE) == SDL_HINT_OVERRIDE);

Version CoreApi::GetCompiledSdlVersion() {
  SDL_version version;
  SDL_VERSION(&version);
  return {version.major, version.minor, version.patch};
}

Version CoreApi::GetLinkedSdlVersion() {
  SDL_version version;
  SDL_GetVersion(&version);
  return {version.major, version.minor, version.patch};
}

std::string CoreApi::GetRevision() { return SDL_GetRevision(); }

int CoreApi::GetRevisionNumber() { return SDL_GetRevisionNumber(); }

CoreApi::CoreApi(Flag flag) : CoreApi(Flags{flag}) {}

CoreApi::CoreApi(const Flags& flags) {
  Uint32 flags_mask = 0;
  for (Flag flag : flags) {
    flags_mask |= static_cast<Uint32>(flag);
  }
  int return_code = SDL_Init(flags_mask);
  if (return_code != 0) {
    throw CoreApiException("Failed to initialize SDL");
  }
}

CoreApi::~CoreApi() { SDL_Quit(); }

void CoreApi::InitSubSystem(Flag flag) { InitSubSystem(Flags{flag}); }

void CoreApi::InitSubSystem(const Flags& flags) {
  Uint32 flags_mask = 0;
  for (Flag flag : flags) {
    flags_mask |= static_cast<Uint32>(flag);
  }
  int return_code = SDL_InitSubSystem(flags_mask);
  if (return_code != 0) {
    throw CoreApiException("Failed to initialize SDL subsystem");
  }
}

void CoreApi::QuitSubSystem(Flag flag) { QuitSubSystem(Flags{flag}); }

void CoreApi::QuitSubSystem(const Flags& flags) {
  Uint32 flags_mask = 0;
  for (Flag flag : flags) {
    flags_mask |= static_cast<Uint32>(flag);
  }
  SDL_QuitSubSystem(flags_mask);
}

CoreApi::Flags CoreApi::WasInit() const {
  Uint32 flags_mask = SDL_WasInit(0);
  Flags result;
  for (Flag flag : {Flag::TIMER, Flag::AUDIO, Flag::VIDEO, Flag::JOYSTICK, Flag::HAPTIC,
                    Flag::GAMECONTROLLER, Flag::EVENTS, Flag::SENSOR, Flag::EVERYTHING}) {
    Uint32 flag_mask = static_cast<Uint32>(flag);
    if ((flags_mask & flag_mask) == flag_mask) {
      result.insert(flag);
    }
  }
  return result;
}

bool CoreApi::WasInit(Flag flag) const {
  Uint32 flag_mask = static_cast<Uint32>(flag);
  return SDL_WasInit(flag_mask) == flag_mask;
}

bool CoreApi::SetHint(const std::string& name, const std::string& value, HintPriority priority) {
  return SDL_SetHintWithPriority(name.c_str(), value.c_str(),
                                 static_cast<SDL_HintPriority>(priority)) == SDL_TRUE;
}

std::optional<std::string> CoreApi::GetHint(const std::string& name) {
  if (const char* value = SDL_GetHint(name.c_str()); value != NULL) {
    return value;
  } else {
    return std::nullopt;
  }
}

bool CoreApi::GetHint(const std::string& name, bool default_value) {
  return SDL_GetHintBoolean(name.c_str(), static_cast<SDL_bool>(default_value)) == SDL_TRUE;
}

void CoreApi::AddHintCallback(const std::string& name, CoreApi::HintCallback callback,
                              void* userdata) {
  auto callback_ptr = *callback.target<SDL_HintCallback>();
  SDL_AddHintCallback(name.c_str(), callback_ptr, userdata);
}

void CoreApi::DelHintCallback(const std::string& name, CoreApi::HintCallback callback,
                              void* userdata) {
  auto callback_ptr = *callback.target<SDL_HintCallback>();
  SDL_DelHintCallback(name.c_str(), callback_ptr, userdata);
}

void CoreApi::ClearHints() { SDL_ClearHints(); }
