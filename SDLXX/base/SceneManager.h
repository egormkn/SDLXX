#ifndef SDLXX_SCENEMANAGER_H
#define SDLXX_SCENEMANAGER_H

#include <stack>
#include <algorithm>
#include "Window.h"
#include "Scene.h"

namespace SDLXX {
    class SceneManager {
    public:
        SceneManager(Window &w, Scene *s) {
            window = &w;
            scenes.push(s);
        }

        ~SceneManager() {
            clear();
            window = nullptr;
        }

        void push(Scene *s) {
            scenes.push(s);
        }

        void pop() {
            scenes.pop();
        }

        void setWindow(Window &w) {
            window = &w;
        }

        Window &getWindow() {
            return *window;
        }

        void clear() {
            while (scenes.size() > 0) {
                scenes.top()->cleanUp();
                delete scenes.top();
                scenes.pop();
            }
        }

        void run() {
            Uint32 t = 0, dt = 10, accumulator = 0;
            Uint32 currentTime = SDL_GetTicks();

            Event e;

            scenes.top()->init(*window);

            //State previous, current;

            while (scenes.size() > 0) {
                Uint32 newTime = SDL_GetTicks();
                Uint32 frameTime = std::min(newTime - currentTime, (Uint32) 250);
                currentTime = newTime;

                Scene *currentScene = scenes.top();

                ////////CHECK/////////
                if(!currentScene->isActive()) {
                    Scene *intent = nullptr;
                    if(currentScene->hasIntent()) {
                        intent = currentScene->getIntent();
                    }
                    delete currentScene;
                    scenes.pop();
                    if(intent != nullptr) {
                        scenes.push(intent);
                    } else if(scenes.size() > 0) {
                        scenes.top()->init(*window);
                    }
                    continue;
                }

                if(currentScene->hasIntent()) {
                    Log::log("Pushing new intent");
                    scenes.push(currentScene->getIntent());
                    currentScene->cleanUp();
                    continue;
                }
                ////////CHECK/////////


                while (e.hasNext()) {
                    if(e.getType() == SDL_QUIT) {
                        clear(); // FIXME Do we really need to quit?
                    } else {
                        currentScene->handleEvent(e);
                    }
                }

                if (scenes.size() == 0) {
                    break;
                }

                accumulator += frameTime;

                while (accumulator >= dt) {
                    //previous = current;
                    //integrate( current, t, dt );
                    scenes.top()->update();
                    t += dt;
                    accumulator -= dt;
                    std::string str = "Game FPS: " + std::to_string((frameTime == 0 ? 0 : (int) (1000.0 / frameTime)));
                    window->setTitle(str);
                }

                const Uint32 alpha = (Uint32) (accumulator / dt);

                //State state;
                //state.x = current.x * alpha + previous.x * (1 - alpha);
                //state.v = current.v * alpha + previous.v * (1 - alpha);
                // render( state );

                scenes.top()->render(window->getRenderer());
            }
        }

    private:
        Window *window = nullptr;
        std::stack<Scene *> scenes;
    };
}

#endif // SDLXX_SCENEMANAGER_H
