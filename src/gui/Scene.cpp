#include <sdlxx/core/Log.h>
#include <sdlxx/gui/Scene.h>

using namespace sdlxx::core;
using namespace sdlxx::gui;

Scene::~Scene() {
  if (intent != nullptr) {
    delete intent;
  }
}

Scene::Scene(const std::string& t) {
  initialized = false;
  paused = false;
  finished = false;  ///< If the scene was cleaned up and needs to be destroyed
  intent = nullptr;
  title = t;
}

void Scene::runIntent(Scene* newIntent) {
  Log::info("[" + title + "] Running intent");
  if (intent != nullptr) {
    delete intent;
  }
  intent = newIntent;
}

void Scene::finish() { setFinished(true); }

bool Scene::hasIntent() const { return intent != nullptr; }

const std::string& Scene::getTitle() const { return title; }

bool Scene::isInitialized() const { return initialized; }

bool Scene::isFinished() const { return finished; }

bool Scene::isPaused() const { return paused; }

void Scene::setInitialized(bool state) {
  Log::info("[" + title + "] Initialized: " + std::to_string(state));
  initialized = state;
}

void Scene::setFinished(bool state) {
  Log::info("[" + title + "] Finished: " + std::to_string(state));
  finished = state;
}

void Scene::setPaused(bool state) { paused = state; }

Scene* Scene::getIntent() {
  Scene* runner = intent;
  intent = nullptr;
  return runner;
}
