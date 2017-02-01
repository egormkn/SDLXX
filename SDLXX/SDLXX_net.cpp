#include <sstream>
#include "SDLXX_net.h"
#include "Exception.h"
#include "Log.h"

std::mutex SDLXX::SDL_net::mutex;

bool SDLXX::SDL_net::initialized = false;

SDLXX::SDL_net::SDL_net() {
#ifndef SDLXX_RELEASE
    Log::log("Initializing SDL network system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw Exception("SDL_net already initialized");
        }
        if(SDLNet_Init() == -1) {
            throw Exception("Unable to initialize SDL_net", SDLNet_GetError());
        }
        initialized = true;
    }
#ifndef SDLXX_RELEASE
    SDL_version compiled;
    const SDL_version *linked = SDLNet_Linked_Version();
    SDL_NET_VERSION(&compiled);
    std::stringstream compiledString, linkedString;
    compiledString << "Compiled against SDL_net v" << (int) compiled.major
                   << '.' << (int) compiled.minor << '.' << (int) compiled.patch;
    linkedString << "Linked against SDL_net v" << (int) linked->major
                 << '.' << (int) linked->minor << '.' << (int) linked->patch;
    Log::log(compiledString.str());
    Log::log(linkedString.str());
    Log::newline();
#endif
}

SDLXX::SDL_net::~SDL_net() {
#ifndef SDLXX_RELEASE
    Log::log("Cleaning up SDL network system...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    SDLNet_Quit();
    initialized = false;
}
