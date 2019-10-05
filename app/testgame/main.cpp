#include <sdlxx/core/SDLXX_core.h>
#include <sdlxx/core/Window.h>
#include <sdlxx/gui/SceneManager.h>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/mixer/SDLXX_mixer.h>
#include <sdlxx/net/SDLXX_net.h>
#include <sdlxx/ttf/SDLXX_ttf.h>

#include "Menu.h"

using namespace sdlxx::core;
using namespace sdlxx::gui;
using namespace sdlxx::image;
using namespace sdlxx::net;
using namespace sdlxx::mixer;
using namespace sdlxx::ttf;

int main(int argc, char* args[]) {
  try {
    SDLXX::setHint("SDL_RENDER_SCALE_QUALITY", "1");
    SDLXX sdlxx({SDLXX::Subsystem::VIDEO, SDLXX::Subsystem::EVENTS});
    SDL_image sdl_image(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_mixer sdl_mixer(0 /*MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG*/);
    SDLXX_net sdlxx_net;
    SDLXX_ttf sdlxx_ttf;

    Window window("The Game", 800, 600,
                  {Window::Option::SHOWN, Window::Option::RESIZABLE,
                   Window::Option::ALLOW_HIGHDPI});

    Renderer renderer(
        window, -1,
        {Renderer::Option::ACCELERATED, Renderer::Option::PRESENTVSYNC});
    renderer.setLogicalSize(800, 600);
    renderer.setColor(0xFFFFFF);

    SceneManager manager;
    std::shared_ptr<Menu> menu = std::make_shared<Menu>("MENU", window);
    manager.push(menu);
    manager.run(window);
  } catch (std::exception& e) {
    // Log::error(e.what());
  }

  return 0;
}
