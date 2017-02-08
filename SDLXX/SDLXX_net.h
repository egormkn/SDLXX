#ifndef SDLXX_NET_H
#define SDLXX_NET_H

#include <mutex>

#include <SDL_net.h>

namespace SDLXX {
    class SDL_net {
    public:
        // Init SDL_net
        SDL_net();

        // Quit SDL_net
        ~SDL_net();

    private:
        // Mutex that allows only one instance of class
        static std::mutex mutex;

        // Initialization status
        static bool initialized;

        // Deleted copy constructor
        // This class is not copyable
        SDL_net(const SDL_net &other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDL_net &operator=(const SDL_net &other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDL_net(SDL_net &&other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDL_net &operator=(SDL_net &&other) = delete;
    };
}

#endif // SDLXX_NET_H
