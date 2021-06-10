#ifndef BUTTON_H
#define BUTTON_H

#include <sdlxx/core/events.h>
#include <sdlxx/core/point.h>

class Button {
public:
  enum Sprite { MOUSE_OUT = 0, MOUSE_OVER_MOTION = 1, MOUSE_DOWN = 2, MOUSE_UP = 3, TOTAL = 4 };

  // Initializes internal variables
  Button();

  // Sets top left position
  void SetPosition(int x, int y);

  // Handles mouse event
  void HandleEvent(const sdlxx::Event& e);

  // Shows button sprite
  void Render();

  sdlxx::Point GetPosition() const;

  Sprite GetSprite() const;

private:
  // Top left position
  sdlxx::Point mPosition = {0, 0};

  // Currently used global sprite
  Sprite mCurrentSprite = Sprite::MOUSE_OUT;
};

#endif  // BUTTON_H
