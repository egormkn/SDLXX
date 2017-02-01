#ifndef SDLXX_STATE_H
#define SDLXX_STATE_H

#include <SDL_events.h>
#include "Event.h"
#include "Renderer.h"
#include "Window.h"

namespace SDLXX {
    class Scene {
    public:
        virtual void init(Window &window) = 0;
        virtual void cleanUp() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void handleEvent(Event &e) = 0;
        virtual void update() = 0;
        virtual void render(Renderer &renderer) = 0;

        virtual bool isActive() const final {
            return active;
        }
        virtual void setActive(bool state) final {
            active = state;
        }

        virtual bool hasIntent() const final {
            return intent != nullptr;
        }

        virtual Scene *getIntent() final {
            Scene *runner = intent;
            intent = nullptr;
            return runner;
        }

    protected:
        virtual void runIntent(Scene *newIntent) final {
            Log::log("Running intent");
            if (intent != nullptr) {
                delete intent;
            }
            intent = newIntent;
        }

    private:
        bool active = false;
        Scene *intent = nullptr;
    };
}

#endif // SDLXX_STATE_H
