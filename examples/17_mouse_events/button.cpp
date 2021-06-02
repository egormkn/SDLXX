#include "button.h"

#include <SDL_events.h>
#include <SDL_mouse.h>

Button::Button() {}

void Button::SetPosition(int x, int y) {
  mPosition.x = x;
  mPosition.y = y;
}

void Button::HandleEvent(const sdlxx::core::Event& e) {
  if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN ||
      e.type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse is in button
    bool inside = true;

    // Mouse is left of the button
    if (x < mPosition.x) {
      inside = false;
    }
    // Mouse is right of the button
    else if (x > mPosition.x + 300) {
      inside = false;
    }
    // Mouse above the button
    else if (y < mPosition.y) {
      inside = false;
    }
    // Mouse below the button
    else if (y > mPosition.y + 200) {
      inside = false;
    }

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

sdlxx::core::Point Button::GetPosition() const { return mPosition; }
