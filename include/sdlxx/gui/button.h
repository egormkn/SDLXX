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
 * \brief Header for the Button class that represents a button.
 */

#ifndef SDLXX_GUI_BUTTON_H
#define SDLXX_GUI_BUTTON_H

#include <utility>

#include <SDL_events.h>
#include <sdlxx/ttf/font.h>

#include "sdlxx/core/log.h"
#include "sdlxx/core/texture.h"
#include "sdlxx/gui/node.h"
#include "sdlxx/image/image_texture.h"

namespace sdlxx {

/**
 * \brief A class that represents a button.
 */
class Button : public Node {
public:
  enum class State { DEFAULT, HOVER, PRESSED, RELEASED };

  explicit Button(std::string text, std::function<void()> handler)
      : Node("button"), text(std::move(text)), handler(std::move(handler)) {}

  void OnActivate() override {
    Node::OnActivate();
    Font font("assets/xkcd-script.ttf", 28);
    Surface text_surface = font.RenderBlended(text, Color::BLACK);
    text_texture = std::make_unique<Texture>(GetContext()->renderer, text_surface);
    text_size = text_surface.GetSize();
  }

  void OnDeactivate() override {
    text_texture = nullptr;
    text_size = {};
    Node::OnDeactivate();
  }

  void Update(Time dt) override { Node::Update(dt); }

  void Render(Renderer& renderer) const override {
    Node::Render(renderer);

    Color fill_color = 0xCCCCCC;
    switch (state) {
      case State::HOVER:
        fill_color = 0xEEEEEE;
        break;
      case State::PRESSED:
        fill_color = 0xFFEEEE;
        break;
      case State::RELEASED:
        fill_color = 0xFFFFFF;
        break;
      case State::DEFAULT:
        break;
    }
    renderer.SetDrawColor(fill_color);
    Rectangle viewport = renderer.GetViewport();
    renderer.Fill();
    Point text_position = {(viewport.width - text_size.width) / 2,
                           (viewport.height - text_size.height) / 2};
    Rectangle text_rectangle = {text_position, text_size};
    renderer.Copy(*text_texture, text_rectangle);
  }

  bool HandleEvent(const Event& e) override {
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
      Point mouse;
      SDL_GetMouseState(&mouse.x, &mouse.y);
      Rectangle viewport = GetContext()->renderer.GetViewport();
      if (viewport.Contains(mouse)) {
        switch (e.type) {
          case SDL_MOUSEMOTION:
            state = State::HOVER;
            break;
          case SDL_MOUSEBUTTONDOWN:
            state = State::PRESSED;
            handler();
            return true;
          case SDL_MOUSEBUTTONUP:
            state = State::RELEASED;
            break;
        }
      } else {
        state = State::DEFAULT;
      }
    }
    return false;
  }


private:
  State state = State::DEFAULT;
  std::string text;
  std::function<void()> handler;
  std::unique_ptr<Texture> text_texture;
  Dimensions text_size;
};

}  // namespace sdlxx

#endif  // SDLXX_GUI_BUTTON_H
