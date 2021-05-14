#include <sdlxx/core/log.h>
#include <sdlxx/core/renderer.h>
#include <sdlxx/core/sdlxx_core.h>
#include <sdlxx/core/window.h>
#include <sdlxx/gui/SceneManager.h>
#include <sdlxx/image/SDLXX_image.h>
#include <sdlxx/mixer/SDLXX_mixer.h>
#include <sdlxx/net/SDLXX_net.h>
#include <sdlxx/ttf/SDLXX_ttf.h>

#include "Menu.h"

using namespace std;
using namespace sdlxx::core;
using namespace sdlxx::gui;
using namespace sdlxx::image;
using namespace sdlxx::net;
using namespace sdlxx::mixer;
using namespace sdlxx::ttf;

int main(int argc, char* args[]) {
  try {
    SDLXX_core::setHint("SDL_RENDER_SCALE_QUALITY", "1");

    SDLXX_core sdlxx_core(
        {SDLXX_core::Subsystem::VIDEO, SDLXX_core::Subsystem::EVENTS});
    SDLXX_image sdlxx_image(
        {SDLXX_image::Subsystem::PNG, SDLXX_image::Subsystem::JPG});
    SDLXX_mixer sdlxx_mixer();
    SDLXX_net sdlxx_net;
    SDLXX_ttf sdlxx_ttf;

    using Flag = Window::Flag;

    shared_ptr<Window> window = std::make_shared<Window>(
        "The Game", 800, 600, Flag::SHOWN | Flag::RESIZABLE | Flag::ALLOW_HIGHDPI);

    using ROption = Renderer::Option;
    shared_ptr<Renderer> renderer =
        window->getRenderer(-1, ROption::ACCELERATED | ROption::PRESENTVSYNC);

    renderer->setLogicalSize(800, 600);
    renderer->setColor(0xFFFFFF);

    SceneManager manager;
    std::shared_ptr<Menu> menu = std::make_shared<Menu>("MENU");
    manager.push(menu);
    manager.run(window);
  } catch (std::exception& e) {
    Log::error("[ERROR] " + std::string(e.what()));
  }

  return 0;
}
