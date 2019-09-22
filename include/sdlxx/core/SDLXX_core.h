#pragma once

#ifndef SDLXX_H
#define SDLXX_H

#include <string>
#include <sstream>
#include <mutex>
#include "Log.h"

#include <SDL.h>
#include <SDL_video.h>

namespace sdlxx::core {
    class SDLXX {
    public:
        // Init SDL
        SDLXX(Uint32 flags);

        // Quit SDL
        ~SDLXX();

        void printDebugInfo() {
            SDL_DisplayMode current;
            for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
                std::stringstream s;
                if(SDL_GetCurrentDisplayMode(i, &current) != 0) {
                    s << "Could not get display mode for video display #" << i << ": " << SDL_GetError();
                } else {
                    s << "Display #" << i << ": " << current.w << "x" << current.h << "px @ "
                      << current.refresh_rate << "hz";
                }
                Log::log(s.str());
            }
        }

        Uint32 wasInit(Uint32 flags);

        void initSubSystem(Uint32 flags);

        void quitSubSystem(Uint32 flags);

        static void setHint(const std::string &name, const std::string &value);

        static void setMainReady();

        static void setScreensaverEnabled(bool enabled) {
            if (enabled) {
                SDL_EnableScreenSaver();
            } else {
                SDL_DisableScreenSaver();
            }
        }

        // static int winRTRunApp(MainFunction mainFunction, void* reserved);

    private:
        // Mutex that allows only one instance of class
        static std::mutex mutex;

        // Initialization status
        static bool initialized;

        // Deleted copy constructor
        // This class is not copyable
        SDLXX(const SDLXX &other) = delete;

        // Deleted assignment operator
        // This class is not copyable
        SDLXX &operator=(const SDLXX &other) = delete;

        // Deleted move constructor
        // This class is not movable
        SDLXX(SDLXX &&other) = delete;

        // Deleted move assignment operator
        // This class is not movable
        SDLXX &operator=(SDLXX &&other) = delete;
    };
} // namespace sdlxx::core::core

#endif // SDLXX_H
