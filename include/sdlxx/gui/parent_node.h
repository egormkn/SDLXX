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
 * \brief Header for the ParentNode class that represents a node of scene graph with its children.
 */

#ifndef SDLXX_GUI_PARENT_NODE_H
#define SDLXX_GUI_PARENT_NODE_H

#include <memory>

#include "sdlxx/gui/node.h"

namespace sdlxx {

class ParentNode : public Node {
public:
  bool HandleEvent(const Event& e) override {
    for (auto& child : children) {
      if (child->HandleEvent(e)) {
        return true;
      }
    }
    return false;
  }

  void Update(Time dt) override {
    for (auto& child : children) {
      child->Update(dt);
    }
  }

  void Render(Renderer& renderer) const override {
    for (const auto& child : children) {
      child->Render(renderer);
    }
  }

  void OnActivate() override {
    for (auto& child : children) {
      child->OnActivate();
    }
  }

  void OnDeactivate() override {
    for (auto& child : children) {
      child->OnDeactivate();
    }
  }

  void SetSize(Dimensions new_size) override {
    Node::SetSize(new_size);
    for (const auto& child : children) {
      child->SetSize(new_size);
    }
  }

  void SetStyle(const Style& new_style) override {
    throw std::runtime_error("Not implemented yet");
  }

  void SetContext(Context* new_context) override {
    Node::SetContext(new_context);
    for (const auto& child : children) {
      child->SetContext(new_context);
    }
  }

protected:
  explicit ParentNode(std::string tag, std::vector<std::unique_ptr<Node>> children = {})
      : Node(std::move(tag)), children(std::move(children)) {}

  std::vector<std::unique_ptr<Node>>& GetChildren() { return children; }

  const std::vector<std::unique_ptr<Node>>& GetChildren() const { return children; }

  std::unique_ptr<Node>& GetChild(size_t i) { return children[i]; }

  const std::unique_ptr<Node>& GetChild(size_t i) const { return children[i]; }

  Node& AddChild(std::unique_ptr<Node> node) {
    children.push_back(std::move(node));
    children.back()->SetContext(GetContext());
    return *children.back();
  }

private:
  std::vector<std::unique_ptr<Node>> children;
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_PARENT_NODE_H
