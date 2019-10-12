#include <memory>

#include <sdlxx/core/Log.h>
#include <sdlxx/core/Timer.h>
#include <sdlxx/gui/SceneManager.h>

using namespace sdlxx::core;
using namespace sdlxx::gui;

void SceneManager::push(std::shared_ptr<Scene> s) { scenes.push(move(s)); }

void SceneManager::pop() { scenes.pop(); }

void SceneManager::clear() {
  while (!scenes.empty()) {
    std::shared_ptr<Scene> scene = scenes.top();
    scene->finish(); // Is it needed? If yes, we should update the window
    scenes.pop();
  }
}

void SceneManager::run(std::shared_ptr<Window> window) {
  uint32_t t = 0, dt = 10, accumulator = 0;
  uint32_t currentTime = Timer::getTicks();

  // State previous, current;

  while (scenes.size() > 0) {
    uint32_t newTime = Timer::getTicks();
    uint32_t frameTime = std::min<uint32_t>(newTime - currentTime, 250);
    currentTime = newTime;

    std::shared_ptr<Scene> currentScene = scenes.top();
    currentScene->window = window;

    if (currentScene->isFinished()) {
      std::shared_ptr<Scene> intent = currentScene->intent;
      scenes.pop();
      if (intent) {
        scenes.push(intent);
      }
      continue;
    }

    if (currentScene->hasIntent()) {
      Log::info("[MANAGER] Pushing new intent");
      currentScene->finish();
      scenes.push(currentScene->intent);
      currentScene->intent.reset();
      continue;
    }

    switch (currentScene->state) {
      case Scene::State::DESTROYED:
        currentScene->onCreate();
        currentScene->state = Scene::State::CREATED;
      case Scene::State::CREATED:
      case Scene::State::STOPPED:
        currentScene->onStart();
        currentScene->state = Scene::State::STARTED;
      case Scene::State::STARTED:
      case Scene::State::PAUSED:
        currentScene->onResume();
        currentScene->state = Scene::State::RESUMED;
      case Scene::State::RESUMED:
        break;
    }

    std::optional<Event> event;
    while (event = Events::poll()) {
      Event e = event.value();
      if (e.type == SDL_QUIT) {
        clear();  // FIXME: Do we really need to quit?
      } else if (currentScene->getState() == Scene::State::RESUMED) {
        currentScene->handleEvent(e);
      }
    }

    if (scenes.size() == 0) {
      break;
    }

    accumulator += frameTime;

    while (accumulator >= dt) {
      // previous = current;
      // integrate( current, t, dt );
      if (currentScene->getState() == Scene::State::RESUMED) {
        currentScene->update(t, dt);
      }
      t += dt;
      accumulator -= dt;
      /*std::string str = "Game FPS: " + std::to_string((frameTime == 0 ? 0 :
      (int) (1000.0 / frameTime))); window->setTitle(str);*/
    }

    const Uint32 alpha = (Uint32)(accumulator / dt);

    // State state;
    // state.x = current.x * alpha + previous.x * (1 - alpha);
    // state.v = current.v * alpha + previous.v * (1 - alpha);
    // render( state );
    if (currentScene->getState() == Scene::State::RESUMED) {
      const std::shared_ptr<sdlxx::core::Renderer> renderer =
          window->getRenderer();
      currentScene->render(*renderer);
    }
  }
}
