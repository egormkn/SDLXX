#ifndef SDLXX_BUTTON_H
#define SDLXX_BUTTON_H

#include <nuklear.h>
#include <sdlxx/core/events.h>
#include <sdlxx/core/texture.h>
#include <sdlxx/core/window.h>

#include "../core/point.h"
#include "../gui/Object.h"

namespace sdlxx::gui {
class Button : public sdlxx::gui::Object {
public:
  Button(int x = 0, int y = 0, int width = 0, int height = 0);

  ~Button();

  void setRelativePosition(int x, int y);

  void setRelativeSize(int x, int y);

  bool handleEvent(const sdlxx::core::Event& e) override;

  void update(uint32_t t, uint32_t dt) override;

  void render(sdlxx::core::Renderer& renderer) override;

  void setText(const std::string& text, const std::shared_ptr<sdlxx::core::Renderer>& renderer);

private:
  std::string text;
  sdlxx::core::Point absPos, relPos;
  sdlxx::core::Point absDim, relDim, windowDim;
  sdlxx::core::Texture* textTexture = nullptr;
  bool mouseOver = false;
};
}  // namespace sdlxx::gui

#endif  // SDLXX_BUTTON_H
