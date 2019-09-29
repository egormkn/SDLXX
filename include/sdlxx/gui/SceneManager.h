/**
 * @file SceneManager.h
 * @author Egor Makarenko
 * @brief Class that represents a manager of graphical scenes
 */

#pragma once

#ifndef SDLXX_GUI_SCENEMANAGER_H
#define SDLXX_GUI_SCENEMANAGER_H

#include <algorithm>
#include <stack>

#include <sdlxx/core/Window.h>
#include <sdlxx/gui/Scene.h>

namespace sdlxx::gui {

class SceneManager {
public:
  SceneManager(sdlxx::core::Window& w);

  ~SceneManager();

  void push(std::shared_ptr<Scene> s);

  void pop();

  void setWindow(sdlxx::core::Window& w);

  sdlxx::core::Window& getWindow();

  void clear();

  void run();

private:
  std::shared_ptr<sdlxx::core::Window> window;
  std::stack<std::shared_ptr<Scene>> scenes;
};
}  // namespace sdlxx::core

#endif  // SDLXX_GUI_SCENEMANAGER_H
