#ifndef SDLXX_SCENE_H
#define SDLXX_SCENE_H

#include <SDL_events.h>
#include "Event.h"
#include "Renderer.h"
#include "Window.h"

namespace SDLXX {
    class Scene {
        friend class SceneManager;

    public:
        virtual void onCreate(Window &window) = 0;
        virtual void onDestroy() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;

        virtual void handleEvent(Event &e) = 0;
        virtual void update(Uint32 t, Uint32 dt) = 0;
        virtual void render(Window &window) = 0;

        virtual ~Scene() {
            if (intent != nullptr) {
                delete intent;
            }
        }

    protected:
        Scene(const std::string &t) {
            initialized = false;
            paused = false;
            finished = false;     ///< If the scene was cleaned up and needs to be destroyed
            intent = nullptr;
            title = t;
        }

        virtual void runIntent(Scene *newIntent) final {
            Log::log("[" + title + "] Running intent");
            if (intent != nullptr) {
                delete intent;
            }
            intent = newIntent;
        }

        virtual void finish() final {
            setFinished(true);
        }

        virtual bool hasIntent() const final {
            return intent != nullptr;
        }

        virtual const std::string &getTitle() const final {
            return title;
        }

    private:
        bool initialized, paused, finished;
        Scene *intent;
        std::string title;

        bool isInitialized() const {
            return initialized;
        }

        bool isFinished() const {
            return finished;
        }

        bool isPaused() const {
            return paused;
        }

        void setInitialized(bool state) {
            Log::log("[" + title + "] Initialized: " + std::to_string(state));
            initialized = state;
        }

        void setFinished(bool state) {
            Log::log("[" + title + "] Finished: " + std::to_string(state));
            finished = state;
        }

        void setPaused(bool state) {
            paused = state;
        }

        Scene *getIntent() {
            Scene *runner = intent;
            intent = nullptr;
            return runner;
        }
    };
}

#endif // SDLXX_SCENE_H
