#include "sdlxx/gui/scene_manager.h"

#include <memory>

#include <SDL_events.h>

#include "sdlxx/core/log.h"
#include "sdlxx/core/timer.h"

using namespace sdlxx::core;
using namespace sdlxx::gui;

SceneManager::SceneManager(Node::Context context)
    : window(window), renderer(renderer) {}

void SceneManager::Push(std::unique_ptr<Scene> scene) { scenes.push(std::move(scene)); }

Scene& SceneManager::Top() { return scenes.top(); }

const Scene& SceneManager::Top() const { return scenes.top(); }

void SceneManager::Pop() {
  scenes.pop();
}

void SceneManager::Clear() {
  while (!scenes.empty()) {
    Scene& scene = scenes.top();
    scene.Finish();  // Is it needed? If yes, we should update the window
    scenes.pop();
  }
}

void SceneManager::Run() {
  uint32_t t = 0, dt = 10, accumulator = 0;
  uint32_t currentTime = Timer::GetTicks();

  // State previous, current;

  while (!scenes.empty()) {
    uint32_t newTime = Timer::GetTicks();
    uint32_t frameTime = std::min<uint32_t>(newTime - currentTime, 250);
    currentTime = newTime;

    Scene& currentScene = scenes.top();

    if (currentScene.GetState() == Scene::State::DESTROYED) {
      std::unique_ptr<Scene> intent = std::move(currentScene.intent);
      scenes.pop();
      if (intent) {
        scenes.push(std::move(*intent.release()));
      }
      continue;
    }

    if (currentScene.intent) {
      Log::Info("[MANAGER] Pushing new intent");
      currentScene.Finish();
      scenes.push(std::move(*currentScene.intent.release()));
      continue;
    }

    switch (currentScene.state) {
      case Scene::State::DESTROYED:
        currentScene.OnCreate();
        currentScene.state = Scene::State::CREATED;
      case Scene::State::CREATED:
      case Scene::State::STOPPED:
        currentScene.OnStart();
        currentScene.state = Scene::State::STARTED;
      case Scene::State::STARTED:
      case Scene::State::PAUSED:
        currentScene.OnResume();
        currentScene.state = Scene::State::RUNNING;
      case Scene::State::RUNNING:
        break;
    }

    Event event;
    while (Events::Poll(&event)) {
      if (event.type == SDL_QUIT) {
        Clear();  // FIXME: Do we really need to quit?
      } else if (currentScene.state == Scene::State::RUNNING) {
        currentScene.HandleEvent(event);
      }
    }

    if (scenes.empty()) {
      break;
    }

    accumulator += frameTime;

    while (accumulator >= dt) {
      // previous = current;
      // integrate( current, t, dt );
      if (currentScene.state == Scene::State::RUNNING) {
        currentScene.Update(t, dt);
      }
      t += dt;
      accumulator -= dt;
      /*std::string str = "Game FPS: " + std::to_string((frameTime == 0 ? 0 :
      (int) (1000.0 / frameTime))); window->SetTitle(str);*/
    }

    const auto alpha = static_cast<Uint32>(accumulator / dt);

    // State state;
    // state.x = current.x * alpha + previous.x * (1 - alpha);
    // state.v = current.v * alpha + previous.v * (1 - alpha);
    // render( state );
    if (currentScene.state == Scene::State::RUNNING) {
      currentScene.Render(renderer);
    }
  }
}
