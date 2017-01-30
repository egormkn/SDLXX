#ifndef SDLXX_IMAGE_H
#define SDLXX_IMAGE_H

#include <mutex>

#ifdef SDL2_IMAGE_FOUND
#include <SDL_image.h>
#endif

namespace SDLXX {
    class SDL_image {
    public:
        // Init SDL_image
        SDL_image(Uint32 flags);

        // Quit SDL_image
        ~SDL_image();

    private:
        // Mutex that allows only one instance of class
        static std::mutex mutex;

        // Initialization status
        static bool initialized;

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
