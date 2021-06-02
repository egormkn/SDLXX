#include "sdlxx/core/core_api.h"

#include <SDL.h>
#include <SDL_hints.h>

using namespace sdlxx::core;

#define ASSERT_INIT(x) static_assert(static_cast<uint32_t>(CoreApi::Flag::x) == SDL_INIT_##x);

ASSERT_INIT(TIMER);
ASSERT_INIT(AUDIO);
ASSERT_INIT(VIDEO);
ASSERT_INIT(JOYSTICK);
ASSERT_INIT(HAPTIC);
ASSERT_INIT(GAMECONTROLLER);
ASSERT_INIT(EVENTS);
ASSERT_INIT(SENSOR);
ASSERT_INIT(NOPARACHUTE);
ASSERT_INIT(EVERYTHING);

#define ASSERT_HINT(x) \
  static_assert(static_cast<SDL_HintPriority>(CoreApi::HintPriority::x) == SDL_HINT_##x);

ASSERT_HINT(DEFAULT);
ASSERT_HINT(NORMAL);
ASSERT_HINT(OVERRIDE);

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

CoreApi::CoreApi(BitMask<Flag> flags) {
  int return_code = SDL_Init(static_cast<Uint32>(flags.value));
  if (return_code != 0) {
    throw CoreApiException("Failed to initialize SDL");
  }
}

CoreApi::~CoreApi() { SDL_Quit(); }

void CoreApi::InitSubSystem(BitMask<Flag> flags) {
  int return_code = SDL_InitSubSystem(static_cast<Uint32>(flags.value));
  if (return_code != 0) {
    throw CoreApiException("Failed to initialize SDL subsystem");
  }
}

void CoreApi::QuitSubSystem(BitMask<Flag> flags) {
  SDL_QuitSubSystem(static_cast<Uint32>(flags.value));
}

BitMask<CoreApi::Flag> CoreApi::WasInit() const { return BitMask<Flag>{SDL_WasInit(0)}; }

bool CoreApi::WasInit(Flag flag) const {
  auto flag_mask = static_cast<Uint32>(flag);
  return SDL_WasInit(flag_mask) == flag_mask;
}

bool CoreApi::SetHint(const std::string& name, const std::string& value, HintPriority priority) {
  return SDL_SetHintWithPriority(name.c_str(), value.c_str(),
                                 static_cast<SDL_HintPriority>(priority)) == SDL_TRUE;
}

std::optional<std::string> CoreApi::GetHint(const std::string& name) {
  if (const char* value = SDL_GetHint(name.c_str()); value != nullptr) {
    return value;
  }
  return std::nullopt;
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
