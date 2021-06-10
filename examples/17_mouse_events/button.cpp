#include "button.h"

#include <SDL_events.h>
#include <SDL_mouse.h>

Button::Button() = default;

void Button::SetPosition(int x, int y) {
  mPosition.x = x;
  mPosition.y = y;
}

void Button::HandleEvent(const sdlxx::Event& e) {
  if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse is in button
    bool inside =
        !(x < mPosition.x || x > mPosition.x + 300 || y < mPosition.y || y > mPosition.y + 200);

    // Mouse is outside button
    if (!inside) {
      mCurrentSprite = Sprite::MOUSE_OUT;
    }
    // Mouse is inside button
    else {
      // Set mouse over sprite
      switch (e.type) {
        case SDL_MOUSEMOTION:
          mCurrentSprite = Sprite::MOUSE_OVER_MOTION;
          break;

        case SDL_MOUSEBUTTONDOWN:
          mCurrentSprite = Sprite::MOUSE_DOWN;
          break;

        case SDL_MOUSEBUTTONUP:
          mCurrentSprite = Sprite::MOUSE_UP;
          break;
      }
    }
  }
}

void Button::Render() {}

Button::Sprite Button::GetSprite() const { return mCurrentSprite; }

sdlxx::Point Button::GetPosition() const { return mPosition; }
