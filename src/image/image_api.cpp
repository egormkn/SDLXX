#include "sdlxx/image/image_api.h"

#include <sstream>
#include <utility>
#include <vector>

#include <SDL_image.h>

using namespace std;
using namespace sdlxx::image;

Version ImageApi::GetCompiledSdlImageVersion() {
  SDL_version compiled;
  SDL_IMAGE_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version ImageApi::GetLinkedSdlImageVersion() {
  const SDL_version* linked = IMG_Linked_Version();  // Pointer to the const static object
  return {linked->major, linked->minor, linked->patch};
}

ImageApi::ImageApi(Flag flag) : ImageApi(Flags{flag}) {}

ImageApi::ImageApi(const Flags& flags) { Init(flags); }

ImageApi::~ImageApi() { IMG_Quit(); }

void ImageApi::Init(Flag flag) { Init(Flags{flag}); }

void ImageApi::Init(const Flags& flags) {
  int flags_mask = 0;
  for (Flag flag : flags) {
    flags_mask |= static_cast<int>(flag);
  }
  int return_code = IMG_Init(flags_mask);
  if (!return_code & flags_mask) {
    ostringstream message;
    message << "Failed to initialize image support for ";
    for (const auto& [flag, name] : vector<pair<Flag, string>>{
             {Flag::JPG, "JPG"}, {Flag::PNG, "PNG"}, {Flag::TIF, "TIF"}, {Flag::WEBP, "WEBP"}}) {
      if (!return_code & flags_mask & static_cast<int>(flag)) {
        message << name << ' ';
      }
    }
    throw ImageApiException(message.str());
  }
}

ImageApi::Flags ImageApi::WasInit() const {
  int flags_mask = IMG_Init(0);
  Flags result;
  for (Flag flag : {Flag::JPG, Flag::PNG, Flag::TIF, Flag::WEBP}) {
    int flag_mask = static_cast<int>(flag);
    if ((flags_mask & flag_mask) == flag_mask) {
      result.insert(flag);
    }
  }
  return result;
}

bool ImageApi::WasInit(Flag flag) const {
  int flag_mask = static_cast<int>(flag);
  return (IMG_Init(0) & flag_mask) == flag_mask;
}
