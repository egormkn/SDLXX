#include "SDLXX_image.h"
#include "Exception.h"

SDLXX::SDL_image::SDL_image(Uint32 flags) {
    int initted = IMG_Init(flags);
    if((initted & flags) != flags) {
        throw SDLXX::Exception("Failed to init required image support");
    }
}

SDLXX::SDL_image::~SDL_image() {
    IMG_Quit();
}

SDLXX::SDL_image &SDLXX::SDL_image::getInstance(Uint32 flags) {
    static SDL_image s(flags);
    return s;
}
