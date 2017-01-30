#include <sstream>
#include "SDLXX.h"
#include "Exception.h"
#include "Log.h"

std::mutex SDLXX::SDL::mutex;

bool SDLXX::SDL::initialized = false;

SDLXX::SDL::SDL(Uint32 flags) {
    Log::log("Initializing SDL subsystems...");
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
}

SDLXX::SDL::~SDL() {
    Log::log("Cleaning up SDL subsystems...");
    // TODO: Quit subsystems?
    std::lock_guard<std::mutex> lock(mutex);
    SDL_Quit();
    initialized = false;
}

Uint32 SDLXX::SDL::wasInit(Uint32 flags) {
    return SDL_WasInit(flags);
}

void SDLXX::SDL::initSubSystem(Uint32 flags) {
    SDL_InitSubSystem(flags);
}

void SDLXX::SDL::quitSubSystem(Uint32 flags) {
    SDL_QuitSubSystem(flags);
}

void SDLXX::SDL::setMainReady() {
    SDL_SetMainReady();
}

void SDLXX::SDL::setHint(const std::string &name, const std::string &value) {
    if(SDL_SetHint(name.c_str(), value.c_str()) == SDL_FALSE) {
        Log::warning(("Failed to set " + name).c_str());
    }
}
