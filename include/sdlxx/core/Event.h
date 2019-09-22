#ifndef SDLXX_EVENT_H
#define SDLXX_EVENT_H

#include <SDL_events.h>
#include "Exception.h"

namespace sdlxx::core {
    class Event {
    public:
        Event();

        ~Event();

        bool hasNext();

        SDL_Event &getEvent();

        Uint32 getType();

        bool pushEvent();

    private:
        SDL_Event *event = nullptr;
    };
}

#endif // SDLXX_EVENT_H
