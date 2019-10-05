#include "Menu.h"

Menu::Menu(const std::string &title, Window &w) : Scene(title) {
  window = &w;
  const std::shared_ptr<Renderer> renderer = w.getRenderer();
  runButton = new Button(-150, -25, 100, 50);
  runButton->setRelativePosition(80, 50);
  runButton->setRelativeSize(20, 0);
  runButton->setText("Новая игра", renderer);

  exitButton = new Button(-150, 35, 100, 50);
  exitButton->setRelativePosition(80, 50);
  exitButton->setRelativeSize(20, 0);
  exitButton->setText("Выход", w.getRenderer());
}

Menu::~Menu() {
    delete runButton;
    delete exitButton;
}

void Menu::onCreate(Window &w) {
    background = new Texture("resources/menu.png", w.getRenderer(), 256, 256);
}

void Menu::onDestroy() {
    delete background;
}

void Menu::handleEvent(const Event &e) {
    if(runButton->handleEvent(e) && e.type == SDL_MOUSEBUTTONDOWN) {
        runIntent(new Game("Game"));
    }
    bool handle = exitButton->handleEvent(e);
    Log::info("test");
    if (handle && e.type == SDL_MOUSEBUTTONDOWN) {
      Log::info("TEST");
      finish();
    }
}

void Menu::update(Uint32 t, Uint32 dt) {
    Dimensions dimensions = window->getSize();
    Point d = {dimensions.width, dimensions.height};
    runButton->update(t, dt, d);
    exitButton->update(t, dt, d);
}

void Menu::render(const std::shared_ptr<sdlxx::core::Renderer>& renderer) {
    renderer->setColor(Color(0xFF000000));
    renderer->clear();
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = window->getSize().width - 1;
    clip.h = window->getSize().height - 1;
    background->fill(static_cast<SDL_Renderer*>(renderer->renderer_ptr), nullptr, &clip);
    runButton->render(renderer);
    exitButton->render(renderer);
    renderer->render();
}
