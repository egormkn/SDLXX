#ifndef SDLXX_SCENEMANAGER_H
#define SDLXX_SCENEMANAGER_H

#include <algorithm>
#include <stack>

#include "Scene.h"
#include "Window.h"

namespace sdlxx::core {
class SceneManager {
public:
  SceneManager(Window& w);

  ~SceneManager();

  void push(Scene* s);

  void pop();

  void setWindow(Window& w);

  Window& getWindow();

  void clear();

  void run();

private:
  int *a, b;
  Window* window = nullptr;
  std::stack<Scene*> scenes;
};
}  // namespace sdlxx::core

#endif  // SDLXX_SCENEMANAGER_H
