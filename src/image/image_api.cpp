#include "sdlxx/image/image_api.h"

#include <sstream>
#include <utility>
#include <vector>
#include <string>

#include <SDL_version.h>
#include <SDL_image.h>

using namespace std;
using namespace sdlxx::core;
using namespace sdlxx::image;

Version ImageApi::GetCompiledSdlImageVersion() {
  SDL_version compiled;
  SDL_IMAGE_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version ImageApi::GetLinkedSdlImageVersion() {
  const SDL_version* linked = IMG_Linked_Version();
  return {linked->major, linked->minor, linked->patch};
}

ImageApi::ImageApi(BitMask<Flag> flags) {
  auto flags_mask = static_cast<uint32_t>(IMG_Init(static_cast<int>(flags.value)));
  if ((~flags_mask & flags.value) != 0U) {
    ostringstream message;
    message << "Failed to initialize image support for ";
    for (const auto& [flag, name] : vector<pair<Flag, string>>{
             {Flag::JPG, "JPG"}, {Flag::PNG, "PNG"}, {Flag::TIF, "TIF"}, {Flag::WEBP, "WEBP"}}) {
      if ((~flags_mask & flags.value & static_cast<uint32_t>(flag)) != 0U) {
        message << name << ' ';
      }
    }
    throw ImageApiException(message.str());
  }
}

ImageApi::~ImageApi() { IMG_Quit(); }

BitMask<ImageApi::Flag> ImageApi::WasInit() {
  auto flags_mask = static_cast<uint32_t>(IMG_Init(0));
  return BitMask<Flag>{flags_mask};
}

bool ImageApi::WasInit(Flag flag) {
  auto flags_mask = static_cast<uint32_t>(IMG_Init(0));
  auto flag_mask = static_cast<uint32_t>(flag);
  return (flags_mask & flag_mask) == flag_mask;
}
