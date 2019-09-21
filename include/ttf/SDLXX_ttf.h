#ifndef SDLXX_TTF_H
#define SDLXX_TTF_H

#include <mutex>

#include <SDL_ttf.h>

namespace SDLXX {
    class SDL_ttf {
    public:
        // Init SDL_ttf
        SDL_ttf();

        // Quit SDL_ttf
        ~SDL_ttf();

    private:
        // Mutex that allows only one instance of class
        static std::mutex mutex;

        // Initialization status
        static bool initialized;

        // Deleted copy constructor
        // This class is not copyable
        SDL_ttf(const SDL_ttf &other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDL_ttf &operator=(const SDL_ttf &other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDL_ttf(SDL_ttf &&other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDL_ttf &operator=(SDL_ttf &&other) = delete;
    };
}

#endif // SDLXX_TTF_H
