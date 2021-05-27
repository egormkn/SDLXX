#include <sdlxx/core/log.h>
#include <sdlxx/core/texture.h>
#include <sdlxx/gui/Button.h>
#include <sdlxx/ttf/Font.h>

using namespace sdlxx::core;
using namespace sdlxx::gui;
using namespace sdlxx::ttf;

Button::Button(int x, int y, int width, int height) {
  Point t = {x, y};
  absPos = {x, y};
  absDim = {width, height};
}

Button::~Button() {
    if (textTexture != nullptr) {
        delete textTexture;
    }
}

void Button::setRelativePosition(int x, int y) {
    relPos = {x, y};
}

void Button::setRelativeSize(int x, int y) {
    relDim = {x, y};
}

bool Button::handleEvent(const Event &e) {
  SDL_Rect fillRect = {(int)(relPos.x * windowDim.x / 100.0f) + absPos.x,
                       (int)(relPos.y * windowDim.y / 100.0f) + absPos.y,
                       (int)(relDim.x * windowDim.x / 100.0f) + absDim.x,
                       (int)(relDim.y * windowDim.y / 100.0f) + absDim.y};

  bool inside = true;
  switch (e.type) {
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      int x, y;
      SDL_GetMouseState(&x, &y);
      if (x < fillRect.x) {
        inside = false;
      }
      // Mouse is right of the button
      else if (x > fillRect.x + fillRect.w) {
        inside = false;
      }
      // Mouse above the button
      else if (y < fillRect.y) {
        inside = false;
      }
      // Mouse below the button
      else if (y > fillRect.y + fillRect.h) {
        inside = false;
      }
      mouseOver = inside;
      return inside;
    default:
      return false;
    }
}

void Button::update(Uint32 t, Uint32 dt) {
    windowDim = {640, 480};
}

void Button::render(Renderer& renderer) {
    int w = (int) (relDim.x * windowDim.x / 100.0f) + absDim.x;
    int h = (int) (relDim.y * windowDim.y / 100.0f) + absDim.y;
    SDL_Rect fillRect = {
            (int) (relPos.x * windowDim.x / 100.0f) + absPos.x,
            (int) (relPos.y * windowDim.y / 100.0f) + absPos.y,
            (int) (relDim.x * windowDim.x / 100.0f) + absDim.x,
            (int) (relDim.y * windowDim.y / 100.0f) + absDim.y
    };

    renderer.setColor(mouseOver ? Color(0xFF8888FF) : Color(0xCCCCCCFF));
    renderer.fillRectangle({fillRect.x, fillRect.y, fillRect.w, fillRect.h});

    Dimensions textSize = textTexture->getDimensions();

    SDL_Rect fillRect2 = {
            (int) (relPos.x * windowDim.x / 100.0f) + absPos.x + (w - textSize.width) / 2,
            (int) (relPos.y * windowDim.y / 100.0f) + absPos.y + (h - textSize.height) / 2,
            textSize.width,
            textSize.height
    };

    renderer.copy(*textTexture, std::nullopt, std::make_optional<Rectangle>(fillRect2.x, fillRect2.y, fillRect2.w, fillRect2.h));
}

void Button::setText(const std::string &text, const std::shared_ptr<Renderer>& renderer) {
    Button::text = text;
    if (textTexture != nullptr) {
        delete textTexture;
    }
    Font font("resources/OpenSans.ttf", 16);
    Text surface = font.render(text, Font::Mode::BLENDED, Color::BLACK);
    textTexture = new Texture(renderer, surface);
}
