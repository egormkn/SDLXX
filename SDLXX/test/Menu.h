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
            runButton = new Button(-150, -25, 100, 50);
            runButton->setRelativePosition(80, 50);
            runButton->setRelativeSize(20, 0);
            runButton->setText("Новая игра", w.getSDLRenderer());

            exitButton = new Button(-150, 35, 100, 50);
            exitButton->setRelativePosition(80, 50);
            exitButton->setRelativeSize(20, 0);
            exitButton->setText("Выход", w.getSDLRenderer());
        }

        ~Menu() {
            delete background;
            delete runButton;
            delete exitButton;
        }

        void onCreate(Window &w) override {
            window = &w;
            background = new Texture("resources/menu.png", w.getSDLRenderer(), 800, 600);
        }

        void onDestroy() override {
            delete background;
        }

        void onPause() override {}

        void onResume() override {}

        void handleEvent(Event &e) override {
            if(runButton->handleEvent(e) && e.getType() == SDL_MOUSEBUTTONDOWN) {
                runIntent(new Game("Game"));
            }
            if(exitButton->handleEvent(e) && e.getType() == SDL_MOUSEBUTTONDOWN) {
                finish();
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            Dimensions d = window->getDimensions();
            runButton->update(t, dt, d);
            exitButton->update(t, dt, d);
        }

        void render(Renderer &renderer) override {
            background->render(renderer.getSDLRenderer());
            runButton->render(renderer);
            exitButton->render(renderer);
            renderer.render();
        }

    private:
        Button *runButton = nullptr;
        Button *exitButton = nullptr;
        Texture *background = nullptr;
        Window *window = nullptr;
    };
}

#endif // SDLXX_SCENETEST_H
