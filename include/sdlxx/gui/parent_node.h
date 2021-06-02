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
 * \brief Header for the ParentNode class that represents a node of scene graph with its children.
 */

#pragma once

#ifndef SDLXX_GUI_PARENT_NODE_H
#define SDLXX_GUI_PARENT_NODE_H

#include "sdlxx/gui/node.h"

namespace sdlxx::gui {

class ParentNode : public Node {
public:
  std::vector<std::unique_ptr<Node>>& GetChildren();

  void Update(uint32_t t, uint32_t dt) override;

  void Render() override;

  bool HandleEvent(const sdlxx::core::Event& e) override;

private:
  std::vector<std::unique_ptr<Node>> children;
};

}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_PARENT_NODE_H
