#include "sdlxx/net/net_api.h"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <SDL_net.h>

using namespace std;
using namespace sdlxx;

Version NetApi::GetCompiledSdlNetVersion() {
  SDL_version compiled;
  SDL_NET_VERSION(&compiled);
  return {compiled.major, compiled.minor, compiled.patch};
}

Version NetApi::GetLinkedSdlNetVersion() {
  const SDL_version* linked = SDLNet_Linked_Version();
  return {linked->major, linked->minor, linked->patch};
}

NetApi::NetApi() {
  int return_code = SDLNet_Init();
  if (return_code != 0) {
    throw NetApiException("Failed to initialize network support: " +
                          std::string(SDLNet_GetError()));
  }
}

NetApi::~NetApi() {
  SDLNet_Quit();
}
