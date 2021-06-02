#include "sdlxx/gui/scene.h"

#include "sdlxx/core/log.h"

using namespace sdlxx::core;
using namespace sdlxx::gui;

Scene::State Scene::GetState() const { return state; }

void Scene::OnCreate() {}

void Scene::OnStart() {}

void Scene::OnResume() {}

void Scene::OnPause() {}

void Scene::OnStop() {}

void Scene::OnDestroy() {}

void Scene::Finish() {
  switch (state) {
    case State::RUNNING:
      OnPause();
      state = State::PAUSED;
    case State::STARTED:
    case State::PAUSED:
      OnStop();
      state = State::STOPPED;
    case State::CREATED:
    case State::STOPPED:
      OnDestroy();
      state = State::DESTROYED;
    case State::DESTROYED:
      break;
  }
}
