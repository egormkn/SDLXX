#ifndef SDLXX_SCENETEST_H
#define SDLXX_SCENETEST_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include <sdlxx/core/Object.h>
#include <sdlxx/gui/Button.h>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/gui/Scene.h>
#include <sdlxx/core/Texture.h>
#include "Game.h"

using namespace sdlxx::gui;

class Menu : public Scene {
public:

    Menu(const std::string &title, Window &w);

    ~Menu();

    void onCreate(Window &w) override;

    void onDestroy() override;

    void onPause() override {}

    void onResume() override {}

    void handleEvent(const Event &e) override;

    void update(Uint32 t, Uint32 dt) override;

    void render(const std::shared_ptr<sdlxx::core::Renderer>& renderer) override;

private:
    Button *runButton = nullptr;
    Button *exitButton = nullptr;
    Texture *background = nullptr;
    Window *window = nullptr;
};

#endif // SDLXX_SCENETEST_H
