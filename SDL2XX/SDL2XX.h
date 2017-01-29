#pragma once
#ifndef SDL2XX_H
#define SDL2XX_H

#ifdef SDL2_FOUND
#include <SDL.h>
#endif

#ifdef SDL2_IMAGE_FOUND
#include <SDL_image.h>
#endif

#ifdef SDL2_TTF_FOUND
#include <SDL_ttf.h>
#endif

#ifdef SDL2_NET_FOUND
#include <SDL_net.h>
#endif

#ifdef SDL2_MIXER_FOUND
#include <SDL_mixer.h>
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
        SDL(const SDL& other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDL& operator=(const SDL& other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDL(SDL&& other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDL& operator=(SDL&& other) = delete;

        Uint32 wasInit(Uint32 flags);

        void initSubSystem(Uint32 flags);

        void quitSubSystem(Uint32 flags);

        static void setMainReady();

        // static int winRTRunApp(MainFunction mainFunction, void* reserved);
    };
}

#endif // SDL2XX_H