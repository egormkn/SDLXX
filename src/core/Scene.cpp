#include <sdlxx/core/Scene.h>

sdlxx::core::Scene::~Scene() {
    if (intent != nullptr) {
        delete intent;
    }
}

sdlxx::core::Scene::Scene(const std::string &t) {
    initialized = false;
    paused = false;
    finished = false;     ///< If the scene was cleaned up and needs to be destroyed
    intent = nullptr;
    title = t;
}

void sdlxx::core::Scene::runIntent(sdlxx::core::Scene *newIntent) {
    Log::log("[" + title + "] Running intent");
    if (intent != nullptr) {
        delete intent;
    }
    intent = newIntent;
}

void sdlxx::core::Scene::finish() {
    setFinished(true);
}

bool sdlxx::core::Scene::hasIntent() const {
    return intent != nullptr;
}

const std::string &sdlxx::core::Scene::getTitle() const {
    return title;
}

bool sdlxx::core::Scene::isInitialized() const {
    return initialized;
}

bool sdlxx::core::Scene::isFinished() const {
    return finished;
}

bool sdlxx::core::Scene::isPaused() const {
    return paused;
}

void sdlxx::core::Scene::setInitialized(bool state) {
    Log::log("[" + title + "] Initialized: " + std::to_string(state));
    initialized = state;
}

void sdlxx::core::Scene::setFinished(bool state) {
    Log::log("[" + title + "] Finished: " + std::to_string(state));
    finished = state;
}

void sdlxx::core::Scene::setPaused(bool state) {
    paused = state;
}

sdlxx::core::Scene *sdlxx::core::Scene::getIntent() {
    Scene *runner = intent;
    intent = nullptr;
    return runner;
}
