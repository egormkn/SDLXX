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
 * \brief Header for the ManualLayout class that represents a layout with manually set dimensions.
 */

#ifndef SDLXX_GUI_LAYOUTS_MANUAL_LAYOUT_H
#define SDLXX_GUI_LAYOUTS_MANUAL_LAYOUT_H

#include "sdlxx/gui/layout.h"

namespace sdlxx {

/**
 * \brief A class that represents a 2D layout.
 */
class ManualLayout : public Layout {
public:
  explicit ManualLayout(std::vector<std::unique_ptr<Node>> children = {},
                        std::vector<Rectangle> positions = {})
      : Layout("manual-layout", std::move(children), std::move(positions)) {}

  Node& AddChild(std::unique_ptr<Node> node, Rectangle position) override {
    return Layout::AddChild(std::move(node), position);
  }
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_LAYOUTS_MANUAL_LAYOUT_H
