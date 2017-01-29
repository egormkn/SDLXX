#include "SDL2XX.h"

SDL::SDL::SDL(Uint32 flags) {
    if(SDL_Init(flags) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        /*
         * Log::error("SDL_Init: Couldn't start SDL");
		 * Log::error(std::string(SDL_GetError()));
		 * throw "SDL Init Fail";
         */
        throw;
    }
}

SDL::SDL::~SDL() {
    // TODO: Quit subsystems
    SDL_Quit();
}

Uint32 SDL::SDL::wasInit(Uint32 flags) {
    return SDL_WasInit(flags);
}

void SDL::SDL::initSubSystem(Uint32 flags) {
    SDL_InitSubSystem(flags);
}

void SDL::SDL::quitSubSystem(Uint32 flags) {
    SDL_QuitSubSystem(flags);
}

void SDL::SDL::setMainReady() {
    SDL_SetMainReady();
}

void SDL::SDL::setHint(const std::string &name, const std::string &value) {
    if(SDL_SetHint(name.c_str(), value.c_str()) == SDL_FALSE) {
        SDL_Log(("Failed to set " + name).c_str()); // FIXME
    }
}
