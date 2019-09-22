#include <sstream>
#include <sdlxx/ttf/SDLXX_ttf.h>
#include <sdlxx/core/Exception.h>
#include <sdlxx/core/Log.h>

std::mutex SDLXX::SDL_ttf::mutex;

bool SDLXX::SDL_ttf::initialized = false;

SDLXX::SDL_ttf::SDL_ttf() {
#ifndef SDLXX_RELEASE
    Log::log("Initializing SDL font rendering system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw Exception("SDL_ttf already initialized");
        }
        if(TTF_Init() == -1) {
            throw Exception("Unable to initialize SDL_ttf", TTF_GetError());
        }
        initialized = true;
    }
#ifndef SDLXX_RELEASE
    SDL_version compiled;
    const SDL_version *linked = TTF_Linked_Version();
    SDL_TTF_VERSION(&compiled);
    std::stringstream compiledString, linkedString;
    compiledString << "Compiled against SDL_ttf v" << (int) compiled.major
                   << '.' << (int) compiled.minor << '.' << (int) compiled.patch;
    linkedString << "Linked against SDL_ttf v" << (int) linked->major
                 << '.' << (int) linked->minor << '.' << (int) linked->patch;
    Log::log(compiledString.str());
    Log::log(linkedString.str());
    Log::newline();
#endif
}

SDLXX::SDL_ttf::~SDL_ttf() {
#ifndef SDLXX_RELEASE
    Log::log("Cleaning up SDL font rendering system...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    TTF_Quit();
    initialized = false;
}
