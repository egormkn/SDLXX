/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer
  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the SceneManager class that represents a manager of graphical scenes.
 * \copyright 
 */

#pragma once

#ifndef SDLXX_GUI_SCENE_MANAGER_H
#define SDLXX_GUI_SCENE_MANAGER_H

#include <stack>

#include "sdlxx/gui/node.h"
#include "sdlxx/gui/scene.h"

namespace sdlxx::gui {

/**
 * \brief A class that represents a manager of graphical scenes.
 */
class SceneManager {
public:
  /**
   * \brief Construct a SceneManager object with the node context
   */
  explicit SceneManager(Node::Context context);

  /**
   * \brief Add a new scene to the top of the stack.
   * \param scene A scene to add to the top of the stack.
   */
  void Push(std::unique_ptr<Scene> scene);

  /**
   * \brief Get a scene on the top of the stack.
   * \return A scene that is on the top of the stack.
   */
  Scene& Top();

  /**
   * \brief Get a scene on the top of the stack.
   * \return A scene that is on the top of the stack.
   */
  const Scene& Top() const;

  /**
   * \brief Remove a scene from the top of the stack.
   */
  Scene Pop();

  /**
   * \brief Clear the stack.
   */
  void Clear();

  /**
   * \brief Run the event loop
   */
  void Run();

private:
  Node::Context context;
  std::stack<std::unique_ptr<Scene>> scenes;
};
}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_SCENE_MANAGER_H
