#include <sstream>
#include <sdlxx/core/SDLXX_core.h>
#include <sdlxx/core/Exception.h>
#include <sdlxx/core/Log.h>

std::mutex sdlxx::core::SDLXX::mutex;

bool sdlxx::core::SDLXX::initialized = false;

sdlxx::core::SDLXX::SDLXX(Uint32 flags) {
#ifndef SDLXX_RELEASE
    Log::log("Initializing SDL subsystems...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw Exception("SDL already initialized");
        }
        if(SDL_Init(flags) != 0) {
            throw Exception("Unable to initialize SDL");
        }
        initialized = true;
    }
#ifndef SDLXX_RELEASE
    SDL_version compiled, linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    std::stringstream compiledString, linkedString;
    compiledString << "Compiled against SDL v" << (int) compiled.major
                   << '.' << (int) compiled.minor << '.' << (int) compiled.patch;
    linkedString << "Linked against SDL v" << (int) linked.major
                 << '.' << (int) linked.minor << '.' << (int) linked.patch;
    Log::log(compiledString.str());
    Log::log(linkedString.str());
    Log::newline();
#endif
}

sdlxx::core::SDLXX::~SDLXX() {
#ifndef SDLXX_RELEASE
    Log::log("Cleaning up SDL subsystems...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    SDL_Quit();
    initialized = false;
}

Uint32 sdlxx::core::SDLXX::wasInit(Uint32 flags) {
    return SDL_WasInit(flags);
}

void sdlxx::core::SDLXX::initSubSystem(Uint32 flags) {
    SDL_InitSubSystem(flags);
}

void sdlxx::core::SDLXX::quitSubSystem(Uint32 flags) {
    SDL_QuitSubSystem(flags);
}

void sdlxx::core::SDLXX::setMainReady() {
    SDL_SetMainReady();
}

void sdlxx::core::SDLXX::setHint(const std::string &name, const std::string &value) {
    if(SDL_SetHint(name.c_str(), value.c_str()) == SDL_FALSE) {
        Log::warning(("Failed to set " + name).c_str());
    }
}
