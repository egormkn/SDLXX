#include "sdlxx/ttf/ttf_api.h"

#include <SDL_ttf.h>

using namespace sdlxx::core;
using namespace sdlxx::ttf;

Version TtfApi::GetCompiledSdlTtfVersion() {
  SDL_version compiled;
  SDL_TTF_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version TtfApi::GetLinkedSdlTtfVersion() {
  const SDL_version* linked = TTF_Linked_Version();
  return {linked->major, linked->minor, linked->patch};
}

TtfApi::TtfApi() {
  int return_code = TTF_Init();
  if (return_code != 0) {
    throw TtfApiException("Failed to initialize TTF support");
  }
}

TtfApi::~TtfApi() { TTF_Quit(); }

bool TtfApi::WasInit() { return TTF_WasInit() != 0; }

void TtfApi::SetByteSwappedUnicode(bool is_swapped) {
  TTF_ByteSwappedUNICODE(static_cast<int>(is_swapped));
}
