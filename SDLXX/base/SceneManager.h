#ifndef SDLXX_STATEMANAGER_H
#define SDLXX_STATEMANAGER_H

#include <stack>
#include "Window.h"
#include "Scene.h"

namespace SDLXX {
    class SceneManager {

    public:
        SceneManager(Window &w, Scene *s) {
            window = &w;
            scenes.push(s);
            s->init(w.getRenderer());
        }

        ~SceneManager() {
            while (scenes.size() > 0) {
                scenes.top()->cleanUp();
                delete scenes.top();
                scenes.pop();
            }
        }

        void run() {



            SDL_Event e;
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                    scenes.top()->handleEvent(e);
                }

                scenes.top()->update();
                scenes.top()->draw(window->getRenderer());
            }


            /*double t = 0.0;
            double dt = 0.01;

            double currentTime = hires_time_in_seconds();
            double accumulator = 0.0;

            State previous;
            State current;

            while (!quit) {
                double newTime = time();
                double frameTime = newTime - currentTime;
                if(frameTime > 0.25)
                    frameTime = 0.25;
                currentTime = newTime;

                accumulator += frameTime;

                while (accumulator >= dt) {
                    previousState = currentState;
                    integrate(currentState, t, dt);
                    t += dt;
                    accumulator -= dt;
                }

                const double alpha = accumulator / dt;

                State state = currentState * alpha +
                              previousState * (1.0 - alpha);

                render(state);
            }*/


        }

    private:
        Window *window = nullptr;
        std::stack<Scene*> scenes;
    };
}

#endif // SDLXX_SCENEMANAGER_H
