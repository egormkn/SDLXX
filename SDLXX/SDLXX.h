#ifndef SDLXX_H
#define SDLXX_H

#include <string>

#ifdef SDL2_FOUND

#include <SDL.h>

#endif

namespace SDLXX {

    class SDL {
    public:
        static SDL &getInstance(Uint32 flags);

        Uint32 wasInit(Uint32 flags);

        void initSubSystem(Uint32 flags);

        void quitSubSystem(Uint32 flags);

        static void setHint(const std::string &name, const std::string &value);

        static void setMainReady();

        // static int winRTRunApp(MainFunction mainFunction, void* reserved);

    private:
        // Init SDL
        SDL();

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
    };
}

#endif // SDLXX_H