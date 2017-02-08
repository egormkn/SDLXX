#ifndef SDLXX_MIXER_H
#define SDLXX_MIXER_H

#include <mutex>

#include <SDL_mixer.h>

namespace SDLXX {
    class SDL_mixer {
    public:
        // Init SDL_mixer
        SDL_mixer(Uint32 flags);

        // Quit SDL_mixer
        ~SDL_mixer();

    private:
        // Mutex that allows only one instance of class
        static std::mutex mutex;

        // Initialization status
        static bool initialized;

        // Deleted copy constructor
        // This class is not copyable
        SDL_mixer(const SDL_mixer &other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDL_mixer &operator=(const SDL_mixer &other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDL_mixer(SDL_mixer &&other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDL_mixer &operator=(SDL_mixer &&other) = delete;
    };
}

#endif // SDLXX_MIXER_H
