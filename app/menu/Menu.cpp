#include "Menu.h"

#include <sdlxx/core/Log.h>
#include <sdlxx/image/Image.h>

using namespace std;
using namespace sdlxx::core;
using namespace sdlxx::gui;
using namespace sdlxx::image;

Menu::Menu(const std::string& title) {
  runButton = make_unique<Button>(-150, -25, 100, 50);
  runButton->setRelativePosition(80, 50);
  runButton->setRelativeSize(20, 0);

  exitButton = make_unique<Button>(-150, 35, 100, 50);
  exitButton->setRelativePosition(80, 50);
  exitButton->setRelativeSize(20, 0);
}

void Menu::onCreate() {
  Log::info("Menu created");
  Image menuImage("resources/menu.png");
  background = make_unique<Texture>(getWindow()->getRenderer(), menuImage);

  runButton->setText("Новая игра", getWindow()->getRenderer());
  exitButton->setText("Выход", getWindow()->getRenderer());
}

void Menu::onStart() {
  Log::info("Menu started");
}

void Menu::onResume() {
  Log::info("Menu resumed");
}

void Menu::onPause() {
  Log::info("Menu paused");
}

void Menu::onStop() {
  Log::info("Menu stopped");
}

void Menu::onDestroy() {
  Log::info("Menu destroyed");
}

bool Menu::handleEvent(const Event& e) {
  if (runButton->handleEvent(e) && e.type == SDL_MOUSEBUTTONDOWN) {
    Log::info("LAUNCH");
  }
  bool handle = exitButton->handleEvent(e);
  if (handle && e.type == SDL_MOUSEBUTTONDOWN) {
    Log::info("TEST");
    finish();
  }
  return true;
}

void Menu::update(uint32_t t, uint32_t dt) {
  Dimensions dimensions = getWindow()->getSize();
  Point d = {dimensions.width, dimensions.height};
  runButton->update(t, dt);
  exitButton->update(t, dt);
}

void Menu::render(Renderer& renderer) {
  /*runButton->setText("Новая игра", );
  exitButton->setText("Выход", renderer);*/

  renderer.setColor(Color(0xFF000000));
  renderer.clear();
  Rectangle clip(0, 0, getWindow()->getSize().width - 1,
                 getWindow()->getSize().height - 1);
  renderer.copy(*background, std::make_optional(clip), std::nullopt);

  // background->fill(static_cast<SDL_Renderer*>(renderer.renderer_ptr),
  // nullptr,
  //                  &clip);
  runButton->render(renderer);
  exitButton->render(renderer);
  renderer.render();
}
