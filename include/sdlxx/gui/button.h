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
 * \brief Header for the Button class that represents a button.
 */

#pragma once

#ifndef SDLXX_GUI_BUTTON_H
#define SDLXX_GUI_BUTTON_H

#include "sdlxx/core/events.h"
#include "sdlxx/core/point.h"
#include "sdlxx/core/texture.h"
#include "sdlxx/core/window.h"
#include "sdlxx/gui/node.h"

namespace sdlxx::gui {

/**
 * \brief A class that represents a button.
 */
class Button : public Node {
public:
  enum class State { DEFAULT, HOVER, PRESSED, RELEASED };

  Button(int x = 0, int y = 0, int width = 0, int height = 0);

  ~Button();

  void setRelativePosition(int x, int y);

  void setRelativeSize(int x, int y);

  void Update(uint32_t t, uint32_t dt) override;

  void Render() override;

  bool HandleEvent(const sdlxx::core::Event& e) override;

  void setText(const std::string& text);

private:
  std::string text;
  sdlxx::core::Point absPos, relPos;
  sdlxx::core::Point absDim, relDim, windowDim;
  sdlxx::core::Texture* textTexture = nullptr;
  bool mouseOver = false;
};

}  // namespace sdlxx::gui

#endif  // SDLXX_GUI_BUTTON_H
