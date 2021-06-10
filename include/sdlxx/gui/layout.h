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
 * \brief Header for the Layout class that represents a 2D layout.
 */

#ifndef SDLXX_GUI_LAYOUT_H
#define SDLXX_GUI_LAYOUT_H

#include <string>

#include "sdlxx/core/log.h"
#include "sdlxx/core/window.h"
#include "sdlxx/gui/parent_node.h"

namespace sdlxx {

/**
 * \brief A class that represents a 2D layout.
 */
class Layout : public ParentNode {
public:
  bool HandleEvent(const Event& e) override {
    Renderer& renderer = GetContext()->renderer;
    Rectangle original_viewport = renderer.GetViewport();
    for (size_t i = 0; i < GetChildren().size(); ++i) {
      renderer.SetViewport(GetPosition(i));
      if (GetChild(i)->HandleEvent(e)) {
        renderer.SetViewport(original_viewport);
        return true;
      }
    }
    renderer.SetViewport(original_viewport);
    return false;
  }

  void Render(Renderer& renderer) const override {
    Rectangle original_viewport = renderer.GetViewport();
    for (size_t i = 0; i < GetChildren().size(); ++i) {
      renderer.SetViewport(GetPosition(i));
      renderer.Fill();
      GetChild(i)->Render(renderer);
    }
    renderer.SetViewport(original_viewport);
  }

  void SetSize(Dimensions new_size) override {
    Node::SetSize(new_size);  // NOLINT(bugprone-parent-virtual-call)
  }

protected:
  explicit Layout(std::string tag, std::vector<std::unique_ptr<Node>> children,
                  std::vector<Rectangle> positions)
      : ParentNode(std::move(tag), std::move(children)), positions(std::move(positions)) {
    GetPositions().resize(GetChildren().size());
  }

  std::vector<Rectangle>& GetPositions() { return positions; }

  const std::vector<Rectangle>& GetPositions() const { return positions; }

  Rectangle& GetPosition(size_t i) { return positions[i]; }

  const Rectangle& GetPosition(size_t i) const { return positions[i]; }

  virtual Node& AddChild(std::unique_ptr<Node> node, Rectangle position) {
    positions.push_back(position);
    return ParentNode::AddChild(std::move(node));
  }

private:
  std::vector<Rectangle> positions;
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_LAYOUT_H
