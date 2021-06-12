#ifndef BUTTON_H
#define BUTTON_H

#include <array>
#include <optional>

#include <sdlxx/core/events.h>
#include <sdlxx/core/point.h>
#include <sdlxx/core/renderable.h>
#include <sdlxx/core/texture.h>

class Button : public sdlxx::Renderable {
public:
  enum Sprite { MOUSE_OUT = 0, MOUSE_OVER_MOTION = 1, MOUSE_DOWN = 2, MOUSE_UP = 3, TOTAL = 4 };

  // Initializes internal variables
  Button();

  // Sets top left position
  void SetPosition(int x, int y);

  void SetSize(sdlxx::Dimensions new_size);

  // Handles mouse event
  void HandleEvent(const sdlxx::Event& e);

  // Shows button sprite
  void Render(sdlxx::Renderer& renderer) const override;

  sdlxx::Point GetPosition() const;

  Sprite GetSprite() const;

  static void SetTexture(sdlxx::Texture new_texture,
                         std::array<sdlxx::Rectangle, Button::Sprite::TOTAL> new_clips);

private:
  static sdlxx::Texture texture;

  static std::array<sdlxx::Rectangle, Button::Sprite::TOTAL> clips;

  // Top left position
  sdlxx::Point position = {0, 0};

  sdlxx::Dimensions size;

  // Currently used global sprite
  Sprite current_sprite = Sprite::MOUSE_OUT;
};

#endif  // BUTTON_H
