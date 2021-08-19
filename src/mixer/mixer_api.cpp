#include "sdlxx/mixer/mixer_api.h"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <SDL_mixer.h>

using namespace std;
using namespace sdlxx;

Version MixerApi::GetCompiledSdlMixerVersion() {
  SDL_version compiled;
  SDL_MIXER_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version MixerApi::GetLinkedSdlMixerVersion() {
  const SDL_version* linked = Mix_Linked_Version();
  return {linked->major, linked->minor, linked->patch};
}

MixerApi::MixerApi(BitMask<Flag> flags) {
  auto flags_mask = static_cast<int>(Mix_Init(static_cast<int>(flags.value)));
  if ((~flags_mask & flags.value) != 0U) {
    ostringstream message;
    message << "Failed to initialize audio support for ";
    for (const auto& [flag, name] : vector<pair<Flag, string>>{{Flag::FLAC, "FLAC"},
                                                               {Flag::MOD, "MOD"},
                                                               {Flag::MP3, "MP3"},
                                                               {Flag::OGG, "OGG"},
                                                               {Flag::MID, "MID"},
                                                               {Flag::OPUS, "OPUS"}}) {
      if ((~flags_mask & flags.value & static_cast<int>(flag)) != 0U) { message << name << ' '; }
    }
    throw MixerApiException(message.str());
  }
}

MixerApi::~MixerApi() {
  Mix_Quit();
}
