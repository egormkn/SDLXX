#include <sdlxx/core/log.h>
#include <sdlxx/gui/Scene.h>

using namespace sdlxx::core;
using namespace sdlxx::gui;

void Scene::update(uint32_t t, uint32_t dt) {}

void Scene::render(Renderer& renderer) {}

bool Scene::handleEvent(const Event& e) { return false; }

Scene::State Scene::getState() const { return state; }

void Scene::onCreate() {}

void Scene::onStart() {}

void Scene::onResume() {}

void Scene::onPause() {}

void Scene::onStop() {}

void Scene::onDestroy() {}

void Scene::launch(std::shared_ptr<Scene> intent) {
  this->intent = move(intent);
}

void Scene::finish() {
  switch (state) {
    case State::RESUMED:
      onPause();
      this->state = State::PAUSED;
    case State::STARTED:
    case State::PAUSED:
      onStop();
      this->state = State::STOPPED;
    case State::CREATED:
    case State::STOPPED:
      onDestroy();
      this->state = State::DESTROYED;
    case State::DESTROYED:
      break;
  }
  finished = true;
}

bool Scene::hasIntent() const { return bool(intent); }

bool Scene::isFinished() const { return finished; }

std::shared_ptr<sdlxx::core::Window> Scene::getWindow() const { return window; }

void Scene::setWindow(std::shared_ptr<Window> window) {
  this->window = move(window);
}
