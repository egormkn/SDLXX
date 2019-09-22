#include <sstream>
#include <sdlxx/ttf/SDLXX_ttf.h>
#include <sdlxx/core/Exception.h>
#include <sdlxx/core/Log.h>

std::mutex sdlxx::ttf::SDL_ttf::mutex;

bool sdlxx::ttf::SDL_ttf::initialized = false;

sdlxx::ttf::SDL_ttf::SDL_ttf() {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Initializing SDL font rendering system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw sdlxx::core::Exception("SDL_ttf already initialized");
        }
        if(TTF_Init() == -1) {
            throw sdlxx::core::Exception("Unable to initialize SDL_ttf", TTF_GetError());
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
    sdlxx::core::Log::log(compiledString.str());
    sdlxx::core::Log::log(linkedString.str());
    sdlxx::core::Log::newline();
#endif
}

sdlxx::ttf::SDL_ttf::~SDL_ttf() {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Cleaning up SDL font rendering system...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    TTF_Quit();
    initialized = false;
}
