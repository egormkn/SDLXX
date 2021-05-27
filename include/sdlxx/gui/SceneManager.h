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

#include <sdlxx/core/window.h>
#include <sdlxx/gui/Scene.h>

namespace sdlxx::gui {

/**
 * @brief Class that represents a manager of graphical scenes
 */
class SceneManager {
public:
  void push(std::shared_ptr<Scene> scene);

  void pop();

  void clear();

  void run(std::shared_ptr<sdlxx::core::Window> window);

private:
  std::stack<std::shared_ptr<Scene>> scenes;
};
}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_SCENEMANAGER_H
