#include <sstream>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/core/Exception.h>
#include <sdlxx/core/Log.h>

std::mutex SDLXX::SDL_image::mutex;

bool SDLXX::SDL_image::initialized = false;

SDLXX::SDL_image::SDL_image(Uint32 flags) {
#ifndef SDLXX_RELEASE
    Log::log("Initializing SDL_image system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw Exception("SDL_image already initialized");
        }
        int initted = IMG_Init(flags);
        if((initted & flags) != flags) {
            throw Exception("Unable to initialize SDL_image", IMG_GetError());
        }
        initialized = true;
    }
#ifndef SDLXX_RELEASE
    SDL_version compiled;
    const SDL_version *linked = IMG_Linked_Version();
    SDL_IMAGE_VERSION(&compiled);
    std::stringstream compiledString, linkedString;
    compiledString << "Compiled against SDL_image v" << (int) compiled.major
                   << '.' << (int) compiled.minor << '.' << (int) compiled.patch;
    linkedString << "Linked against SDL_image v" << (int) linked->major
                 << '.' << (int) linked->minor << '.' << (int) linked->patch;
    Log::log(compiledString.str());
    Log::log(linkedString.str());
    Log::newline();
#endif
}

SDLXX::SDL_image::~SDL_image() {
#ifndef SDLXX_RELEASE
    Log::log("Cleaning up SDL tmx_image system...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    IMG_Quit();
    initialized = false;
}
