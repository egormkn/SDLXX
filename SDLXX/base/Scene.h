#ifndef SDLXX_STATE_H
#define SDLXX_STATE_H

#include <SDL_events.h>
#include "Event.h"
#include "Renderer.h"

namespace SDLXX {
    class Scene {
    public:
        virtual void init(Renderer &renderer) = 0;
        virtual void cleanUp() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void handleEvent(SDL_Event &e) = 0;
        virtual void update() = 0;
        virtual void draw(Renderer &renderer) = 0;
    };
}

#endif // SDLXX_STATE_H
