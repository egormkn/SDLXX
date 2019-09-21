#include "Scene.h"

SDLXX::Scene::~Scene() {
    if (intent != nullptr) {
        delete intent;
    }
}

SDLXX::Scene::Scene(const std::string &t) {
    initialized = false;
    paused = false;
    finished = false;     ///< If the scene was cleaned up and needs to be destroyed
    intent = nullptr;
    title = t;
}

void SDLXX::Scene::runIntent(SDLXX::Scene *newIntent) {
    Log::log("[" + title + "] Running intent");
    if (intent != nullptr) {
        delete intent;
    }
    intent = newIntent;
}

void SDLXX::Scene::finish() {
    setFinished(true);
}

bool SDLXX::Scene::hasIntent() const {
    return intent != nullptr;
}

const std::string &SDLXX::Scene::getTitle() const {
    return title;
}

bool SDLXX::Scene::isInitialized() const {
    return initialized;
}

bool SDLXX::Scene::isFinished() const {
    return finished;
}

bool SDLXX::Scene::isPaused() const {
    return paused;
}

void SDLXX::Scene::setInitialized(bool state) {
    Log::log("[" + title + "] Initialized: " + std::to_string(state));
    initialized = state;
}

void SDLXX::Scene::setFinished(bool state) {
    Log::log("[" + title + "] Finished: " + std::to_string(state));
    finished = state;
}

void SDLXX::Scene::setPaused(bool state) {
    paused = state;
}

SDLXX::Scene *SDLXX::Scene::getIntent() {
    Scene *runner = intent;
    intent = nullptr;
    return runner;
}