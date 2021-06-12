#include "./button.h"

#include <utility>

#include <SDL_events.h>
#include <SDL_mouse.h>
#include <sdlxx/core/renderer.h>

sdlxx::Texture Button::texture;

std::array<sdlxx::Rectangle, Button::Sprite::TOTAL> Button::clips;

Button::Button() = default;

void Button::SetPosition(int x, int y) {
  position.x = x;
  position.y = y;
}

void Button::SetSize(sdlxx::Dimensions new_size) { size = new_size; }

void Button::HandleEvent(const sdlxx::Event& e) {
  if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x{}, y{};
    SDL_GetMouseState(&x, &y);

    // Mouse is outside button
    if (x < position.x || x > position.x + size.width || y < position.y ||
        y > position.y + size.height) {
      current_sprite = Sprite::MOUSE_OUT;
    } else {  // Mouse is inside button
      // Set mouse over sprite
      switch (e.type) {
        case SDL_MOUSEMOTION:
          current_sprite = Sprite::MOUSE_OVER_MOTION;
          break;

        case SDL_MOUSEBUTTONDOWN:
          current_sprite = Sprite::MOUSE_DOWN;
          break;

        case SDL_MOUSEBUTTONUP:
          current_sprite = Sprite::MOUSE_UP;
          break;
      }
    }
  }
}

void Button::Render(sdlxx::Renderer& renderer) const {
  renderer.Copy(texture, clips.at(current_sprite),
                {position.x, position.y, size.width, size.height});
}

Button::Sprite Button::GetSprite() const { return current_sprite; }

sdlxx::Point Button::GetPosition() const { return position; }

void Button::SetTexture(sdlxx::Texture new_texture,
                        std::array<sdlxx::Rectangle, Button::Sprite::TOTAL> new_clips) {
  texture = std::move(new_texture);
  clips = new_clips;
}
