#ifndef SDLXX_SCENE_H
#define SDLXX_SCENE_H

#include <SDL_events.h>
#include "Event.h"
#include "Renderer.h"
#include "Window.h"

namespace sdlxx::core {
    class Scene {
        friend class SceneManager;

    public:
        virtual void onCreate(Window &window) = 0;

        virtual void onDestroy() = 0;

        virtual void onPause() = 0;

        virtual void onResume() = 0;

        virtual void handleEvent(Event &e) = 0;

        virtual void update(Uint32 t, Uint32 dt) = 0;

        virtual void render(Renderer &renderer) = 0;

        virtual ~Scene();

    protected:
        Scene(const std::string &t);

        virtual void runIntent(Scene *newIntent) final;

        virtual void finish() final;

        virtual bool hasIntent() const final;

        virtual const std::string &getTitle() const final;

    private:
        bool initialized, paused, finished;
        Scene *intent;
        std::string title;

        bool isInitialized() const;

        bool isFinished() const;

        bool isPaused() const;

        void setInitialized(bool state);

        void setFinished(bool state);

        void setPaused(bool state);

        Scene *getIntent();
    };
}

#endif // SDLXX_SCENE_H
