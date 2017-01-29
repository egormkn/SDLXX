#ifndef SDLXX_H
#define SDLXX_H

#include <string>

#ifdef SDL2_FOUND
#include <SDL.h>
#endif

namespace SDL {

    class SDL {
    public:
        // Init SDL
        SDL(Uint32 flags);

        // Quit SDL
        ~SDL();

        // Deleted copy constructor
        // This class is not copyable
        SDL(const SDL &other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDL &operator=(const SDL &other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDL(SDL &&other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDL &operator=(SDL &&other) = delete;

        Uint32 wasInit(Uint32 flags);

        void initSubSystem(Uint32 flags);

        void quitSubSystem(Uint32 flags);

        static void setHint(const std::string &name, const std::string &value);

        static void setMainReady();

        // static int winRTRunApp(MainFunction mainFunction, void* reserved);
    };
}

#endif // SDLXX_H