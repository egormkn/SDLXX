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

        Menu(const std::string &title, Window &w);

        ~Menu();

        void onCreate(Window &w) override;

        void onDestroy() override;

        void onPause() override {}

        void onResume() override {}

        void handleEvent(Event &e) override;

        void update(Uint32 t, Uint32 dt) override;

        void render(Renderer &renderer) override;

    private:
        Button *runButton = nullptr;
        Button *exitButton = nullptr;
        Texture *background = nullptr;
        Window *window = nullptr;
    };
};

#endif // SDLXX_SCENETEST_H
