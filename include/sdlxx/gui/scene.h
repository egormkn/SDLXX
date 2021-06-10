/*
  SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)

  Copyright (C) 2019-2021 Egor Makarenko <egormkn@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file
 * \brief Header for the Scene class that represents a 2D scene.
 */

#ifndef SDLXX_GUI_SCENE_H
#define SDLXX_GUI_SCENE_H

#include <cstdint>

#include "sdlxx/core/events.h"
#include "sdlxx/core/log.h"
#include "sdlxx/core/renderer.h"
#include "sdlxx/core/window.h"
#include "sdlxx/gui/parent_node.h"

namespace sdlxx {

class Scene : public ParentNode {
public:
  const std::string& GetName() const { return name; }

  Node& GetRoot() { return *GetChildren().back(); }

  bool IsActive() const { return is_active; }

  bool HasIntent() const { return intent != nullptr; }

protected:
  explicit Scene(std::string name) : ParentNode("scene"), name(std::move(name)) {}

  Scene(std::string name, std::unique_ptr<Node> root)
      : ParentNode("scene", {}), name(std::move(name)) {
    Node& root_node = AddChild(std::move(root));
  }

  void OnActivate() override {
    Log::Info("Started scene " + GetName());
    ParentNode::OnActivate();
  }

  void OnDeactivate() override {
    ParentNode::OnDeactivate();
    Log::Info("Stopped scene " + GetName());
  }

  void SetIntent(std::unique_ptr<Scene> new_intent) { intent = std::move(new_intent); }

  void Finish() { Deactivate(); }

private:
  bool is_active = false;
  std::string name;
  std::unique_ptr<Scene> intent;

  void Activate() {
    if (is_active) {
      throw std::runtime_error("Scene is already activated");
    }
    is_active = true;
    OnActivate();
  }

  void Deactivate() {
    if (!is_active) {
      throw std::runtime_error("Scene is already deactivated");
    }
    OnDeactivate();
    is_active = false;
  }

  friend class SceneManager;
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_SCENE_H
