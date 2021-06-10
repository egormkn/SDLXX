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
 * \brief Header for the Node class that represents a basic node of scene graph.
 */

#ifndef SDLXX_GUI_NODE_H
#define SDLXX_GUI_NODE_H

#include <limits>
#include <stdexcept>

#include "sdlxx/core/events.h"
#include "sdlxx/core/object.h"
#include "sdlxx/core/renderer.h"
#include "sdlxx/core/time.h"
#include "sdlxx/gui/style.h"

namespace sdlxx {

class Node : public Object {
public:
  struct Context {
    Window& window;
    Renderer& renderer;
  };

  bool HandleEvent(const Event& e) override { return false; }

  void Update(Time dt) override {}

  void Render(Renderer& renderer) const override {}

  virtual void OnActivate() {}

  virtual void OnDeactivate() {}

  virtual void SetSize(Dimensions new_size) { size = new_size; }

  virtual void SetStyle(const Style& new_style) { throw std::runtime_error("Not implemented yet"); }

  virtual void SetContext(Context* new_context) { context = new_context; }

  const std::string& GetTag() const { return tag; }

  Dimensions GetSize() const { return size; }

  Style& GetStyle() { return style; }

  Context* GetContext() const { return context; }

protected:
  explicit Node(std::string tag) : tag(std::move(tag)) {}

private:
  const std::string tag;
  Dimensions size;
  Style style;
  Context* context = nullptr;
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_NODE_H
