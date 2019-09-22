#include "Menu.h"

Menu::Menu(const std::string &title, Window &w) : Scene(title) {
    runButton = new Button(-150, -25, 100, 50);
    runButton->setRelativePosition(80, 50);
    runButton->setRelativeSize(20, 0);
    runButton->setText("Новая игра", w.getSDLRenderer());

    exitButton = new Button(-150, 35, 100, 50);
    exitButton->setRelativePosition(80, 50);
    exitButton->setRelativeSize(20, 0);
    exitButton->setText("Выход", w.getSDLRenderer());
}

Menu::~Menu() {
    delete runButton;
    delete exitButton;
}

void Menu::onCreate(Window &w) {
    window = &w;
    background = new Texture("resources/menu.png", w.getSDLRenderer(), 256, 256);
}

void Menu::onDestroy() {
    delete background;
}

void Menu::handleEvent(Event &e) {
    if(runButton->handleEvent(e) && e.getType() == SDL_MOUSEBUTTONDOWN) {
        runIntent(new Game("Game"));
    }
    if(exitButton->handleEvent(e) && e.getType() == SDL_MOUSEBUTTONDOWN) {
        finish();
    }
}

void Menu::update(Uint32 t, Uint32 dt) {
    Dimensions d = window->getDimensions();
    runButton->update(t, dt, d);
    exitButton->update(t, dt, d);
}

void Menu::render(Renderer &renderer) {
    renderer.setColor(Color(0xFF000000));
    renderer.clear();
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = window->getDimensions().getX() - 1;
    clip.h = window->getDimensions().getY() - 1;
    background->fill(renderer.getSDLRenderer(), nullptr, &clip);
    runButton->render(renderer);
    exitButton->render(renderer);
    renderer.render();
}
