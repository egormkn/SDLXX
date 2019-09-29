#include <sstream>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/core/Log.h>

std::mutex sdlxx::image::SDL_image::mutex;

bool sdlxx::image::SDL_image::initialized = false;

sdlxx::image::SDL_image::SDL_image(Uint32 flags) {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Initializing SDL_image system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw std::runtime_error("SDL_image already initialized");
        }
        int initted = IMG_Init(flags);
        if((initted & flags) != flags) {
            throw std::runtime_error("Unable to initialize SDL_image" + std::string(IMG_GetError()));
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
    sdlxx::core::Log::log(compiledString.str());
    sdlxx::core::Log::log(linkedString.str());
    sdlxx::core::Log::newline();
#endif
}

sdlxx::image::SDL_image::~SDL_image() {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Cleaning up SDL tmx_image system...");
#endif
    std::lock_guard<std::mutex> lock(mutex);
    IMG_Quit();
    initialized = false;
}
