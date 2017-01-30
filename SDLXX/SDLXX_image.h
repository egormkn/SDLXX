#ifndef SDLXX_IMAGE_H
#define SDLXX_IMAGE_H

#ifdef SDL2_IMAGE_FOUND
#include <SDL_image.h>
#endif

namespace SDLXX {

    class SDL_image {
    public:
        static SDL_image &getInstance(Uint32 flags);

    private:
        // Init SDL
        SDL_image(Uint32 flags);

        // Quit SDL
        ~SDL_image();

        // Deleted copy constructor
        // This class is not copyable
        SDL_image(const SDL_image &other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDL_image &operator=(const SDL_image &other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDL_image(SDL_image &&other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDL_image &operator=(SDL_image &&other) = delete;
    };
}

#endif // SDLXX_IMAGE_H
