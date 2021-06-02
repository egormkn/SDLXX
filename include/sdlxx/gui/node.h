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
 * \brief Header for the Node class that represents a basic node of scene graph.
 */

#pragma once

#ifndef SDLXX_GUI_NODE_H
#define SDLXX_GUI_NODE_H

#include "sdlxx/core/events.h"
#include "sdlxx/core/renderer.h"
#include "sdlxx/core/window.h"

namespace sdlxx::gui {

class Node {
public:
  struct Context {
    sdlxx::core::Window& window;
    sdlxx::core::Renderer& renderer;
  };

  virtual void OnLoad();

  virtual void OnUnload();

  virtual void Update(uint32_t t, uint32_t dt);

  virtual void Render();

  virtual bool HandleEvent(const sdlxx::core::Event& e);

  virtual ~Node() = default;

  void SetMinSize(sdlxx::core::Dimensions size);

  void SetPrefSize(sdlxx::core::Dimensions size);

  void SetMaxSize(sdlxx::core::Dimensions size);

  sdlxx::core::Window& GetWindow() const;

  sdlxx::core::Renderer& GetRenderer() const;

private:
  Context* context = nullptr;
  sdlxx::core::Dimensions min_size = {-1, -1};
  sdlxx::core::Dimensions pref_size = {-1, -1};
  sdlxx::core::Dimensions max_size = {-1, -1};

  void SetContext(Context* ptr);
};

}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_NODE_H
