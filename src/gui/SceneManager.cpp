#include <SDL_timer.h>
#include <sdlxx/core/Log.h>
#include <sdlxx/gui/SceneManager.h>
#include <memory>

using namespace sdlxx::core;
using namespace sdlxx::gui;

void SceneManager::push(std::shared_ptr<Scene> s) { scenes.push(s); }

void SceneManager::pop() { scenes.pop(); }

void SceneManager::clear() {
  while (!scenes.empty()) {
    std::shared_ptr<Scene> scene = scenes.top();
    if (scene->isInitialized()) {
      scene->setFinished(true);
      scene->setInitialized(false);
      scene->onDestroy();
    }
    scenes.pop();
  }
}

void SceneManager::run(sdlxx::core::Window& window) {
  Uint32 t = 0, dt = 10, accumulator = 0;
  Uint32 currentTime = SDL_GetTicks();

  Event e;
  // State previous, current;

  while (scenes.size() > 0) {
    Uint32 newTime = SDL_GetTicks();
    Uint32 frameTime = std::min(newTime - currentTime, (Uint32)250);
    currentTime = newTime;

    std::shared_ptr<Scene> currentScene = scenes.top();

    if (currentScene->isFinished()) {
      std::shared_ptr<Scene> intent = nullptr;
      if (currentScene->hasIntent()) {
        intent = std::shared_ptr<Scene>(currentScene->getIntent());
      }
      currentScene->setInitialized(false);
      currentScene->onDestroy();
      // delete currentScene;
      scenes.pop();
      if (intent != nullptr) {
        scenes.push(intent);
      }
      continue;
    }

    if (currentScene->hasIntent()) {
      Log::info("[MANAGER] Pushing new intent");
      currentScene->setInitialized(false);
      currentScene->setFinished(false);
      currentScene->onDestroy();
      scenes.push(std::shared_ptr<Scene>(currentScene->getIntent()));
      continue;
    }

    if (!currentScene->isInitialized()) {
      currentScene->onCreate(window);
      currentScene->setInitialized(true);
      currentScene->setFinished(false);
    }

    while (Events::inQueue()) {
      e = Events::poll().value();
      if (e.type == SDL_QUIT) {
        clear();  // FIXME: Do we really need to quit?
      } else if (!currentScene->isFinished()) {
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
      if (!currentScene->isFinished()) {
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
    if (!currentScene->isFinished()) {
      const std::shared_ptr<sdlxx::core::Renderer> renderer = window.getRenderer();
      currentScene->render(renderer);
    }
  }
}