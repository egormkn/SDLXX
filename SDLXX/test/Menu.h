#ifndef SDLXX_SCENETEST_H
#define SDLXX_SCENETEST_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../base/Object.h"
#include "../gui/Button.h"
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "Game.h"

namespace SDLXX {
    class Menu : public Scene {
    public:

        Menu(const std::string &title, Window &w) : Scene(title) {
            Log::log("[" + getTitle() + "] Scene constructed");


            Button *runButton = new Button(-100, -25, 200, 50);
            runButton->setRelativePosition(50, 50);
            runButton->setText("Run", w.getSDLRenderer());
            objects.push_back((Object *&&) runButton);

            Button *exitButton = new Button(-100, 35, 200, 50);
            exitButton->setRelativePosition(50, 50);
            exitButton->setText("Exit", w.getSDLRenderer());
            objects.push_back((Object *&&) exitButton);
        }

        ~Menu() {
            Log::log("[" + getTitle() + "] Scene destructed");
            for (std::vector<Object *>::iterator it = objects.begin() ; it != objects.end(); ++it) {
                delete *it;
            }
            objects.clear();
        }

        void onCreate(Window &w) override {
            Log::log("[" + getTitle() + "] Scene created");


            window = &w;
            // Init resources
            // After: setInitialized(true);


            std::string path = "resources/background.jpg";

            image2 = new Texture(path, w.getSDLRenderer());
        }

        void onDestroy() override {
            Log::log("[" + getTitle() + "] Scene destroyed");
            delete image2;
        }

        void onPause() override {
            // Save state
            // After: setPaused(true);
        }

        void onResume() override {
            // Restore state
            // After: setPaused(false);
        }

        void handleEvent(Event &e) override {
            if(e.getType() == SDL_KEYDOWN) {
                if(e.getEvent().key.keysym.sym == SDLK_UP) {
                    Log::log("[" + getTitle() + "] UP");
                    runIntent(new Game("Game"));
                    // finish();
                    // My changes
                } else {
                    finish();
                }
            }
            if(objects[0]->handleEvent(e)) {
                if (e.getType() == SDL_MOUSEBUTTONDOWN) {
                    runIntent(new Game("Game"));
                }
            }
            if(objects[1]->handleEvent(e)) {
                if (e.getType() == SDL_MOUSEBUTTONDOWN) {
                    finish();
                }
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            Dimensions d = window->getDimensions();

            objects[0]->update(t, dt, d);
            objects[1]->update(t, dt, d);
        }

        void render(Renderer &renderer) override {
            /*renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            SDL_Rect fillRect = {
                    pos, 10, 100, 100
            };

            renderer.setColor(Color(0xFF8888FF));
            SDL_RenderFillRect(renderer.getSDLRenderer(), &fillRect);
            renderer.render();*/
            //SDL_RenderCopy(renderer.getSDLRenderer(), image, NULL, NULL);
            image2->render(renderer.getSDLRenderer());
            // renderer.renderCopy(Texture(image));
            objects[0]->render(renderer);
            objects[1]->render(renderer);
            renderer.render();
        }

    private:
        int pos = 0;
        bool loaded = false;
        std::vector<Object *> objects;
        Texture *image2 = nullptr;
        Window *window = nullptr;
    };
}

#endif // SDLXX_SCENETEST_H
