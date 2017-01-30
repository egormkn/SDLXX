#include "SDLXX.h"
#include "Exception.h"

SDLXX::SDL &SDLXX::SDL::getInstance(Uint32 flags) {
    static SDL s;
    s.initSubSystem(flags);
    return s;
}

SDLXX::SDL::SDL() {
    if(SDL_Init(0) != 0) {
        throw Exception("Unable to initialize SDL");
    }
}

SDLXX::SDL::~SDL() {
    // TODO: Quit subsystems
    SDL_Quit();
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
        SDL_Log(("Failed to set " + name).c_str()); // FIXME
    }
}
