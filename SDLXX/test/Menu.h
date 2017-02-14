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

            Button *runButton = new Button(-150, -25, 100, 50);
            runButton->setRelativePosition(80, 50);
            runButton->setRelativeSize(20, 0);
            runButton->setText("Новая игра", w.getSDLRenderer());
            objects.push_back((Object *&&) runButton);

            Button *exitButton = new Button(-150, 35, 100, 50);
            exitButton->setRelativePosition(80, 50);
            exitButton->setRelativeSize(20, 0);
            exitButton->setText("Выход", w.getSDLRenderer());
            objects.push_back((Object *&&) exitButton);
        }

        ~Menu() {
            Log::log("[" + getTitle() + "] Scene destructed");
            for (std::vector<Object *>::iterator it = objects.begin(); it != objects.end(); ++it) {
                delete *it;
            }
            objects.clear();
        }

        void onCreate(Window &w) override {
            Log::log("[" + getTitle() + "] Scene created");
            window = &w;
            image2 = new Texture("resources/menu.png", w.getSDLRenderer());
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
            if(objects[0]->handleEvent(e) && e.getType() == SDL_MOUSEBUTTONDOWN) {
                runIntent(new Game("Game"));
            }
            if(objects[1]->handleEvent(e) && e.getType() == SDL_MOUSEBUTTONDOWN) {
                finish();
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            Dimensions d = window->getDimensions();
            objects[0]->update(t, dt, d);
            objects[1]->update(t, dt, d);
        }

        void render(Renderer &renderer) override {
            image2->render(renderer.getSDLRenderer());
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
