#include <sstream>
#include <sdlxx/net/SDLXX_net.h>
#include <sdlxx/core/Exception.h>
#include <sdlxx/core/Log.h>

std::mutex sdlxx::net::SDL_net::mutex;

bool sdlxx::net::SDL_net::initialized = false;

sdlxx::net::SDL_net::SDL_net() {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Initializing SDL network system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw sdlxx::core::Exception("SDL_net already initialized");
        }
        if(SDLNet_Init() == -1) {
            throw sdlxx::core::Exception("Unable to initialize SDL_net", SDLNet_GetError());
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
    sdlxx::core::Log::log(compiledString.str());
    sdlxx::core::Log::log(linkedString.str());
    sdlxx::core::Log::newline();
#endif
}

sdlxx::net::SDL_net::~SDL_net() {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Cleaning up SDL network system...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    SDLNet_Quit();
    initialized = false;
}
