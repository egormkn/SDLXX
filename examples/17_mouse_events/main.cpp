#include <SDL_events.h>
#include <sdlxx/core/core_api.h>
#include <sdlxx/core/events.h>
#include <sdlxx/core/log.h>
#include <sdlxx/core/renderer.h>
#include <sdlxx/core/surface.h>
#include <sdlxx/core/window.h>
#include <sdlxx/image/image_api.h>
#include <sdlxx/image/image_surface.h>
#include <sdlxx/image/image_texture.h>
#include <sdlxx/ttf/font.h>
#include <sdlxx/ttf/ttf_api.h>

#include "./button.h"

using namespace std;
using namespace sdlxx::core;
using namespace sdlxx::image;
using namespace sdlxx::ttf;

int main(int argc, char* args[]) {
  try {
    CoreApi core_api(CoreApi::Flag::VIDEO);
    if (!CoreApi::SetHint("SDL_RENDER_SCALE_QUALITY", "1")) {
      Log::Warning("Linear texture filtering is not enabled");
    }

    ImageApi image_api(ImageApi::Flag::PNG);

    TtfApi ttf_api;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Window window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, Window::Flag::SHOWN);

    Renderer renderer(window, Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
    renderer.SetDrawColor(Color::WHITE);

    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 200;
    const int TOTAL_BUTTONS = 4;

    std::array<Rectangle, Button::Sprite::TOTAL> clips;
    Texture texture = ImageTexture(renderer, "button.png");
    std::array<Button, TOTAL_BUTTONS> buttons;

    for (int i = 0; i < clips.size(); ++i) {
      clips[i].x = 0;
      clips[i].y = i * 200;
      clips[i].width = BUTTON_WIDTH;
      clips[i].height = BUTTON_HEIGHT;
    }

    // Set buttons in corners
    buttons[0].SetPosition(0, 0);
    buttons[1].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    buttons[2].SetPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    buttons[3].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);

    Event e;
    bool quit = false;

    while (!quit) {
      while (Events::Poll(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }

        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
          buttons.at(i).HandleEvent(e);
        }
      }

      renderer.SetDrawColor(Color::WHITE);
      renderer.Clear();

      for (int i = 0; i < TOTAL_BUTTONS; ++i) {
        // buttons[i].Render();
        Point position = buttons.at(i).GetPosition();
        renderer.Copy(texture, clips.at(buttons.at(i).GetSprite()),
                      {position.x, position.y, BUTTON_WIDTH, BUTTON_HEIGHT});
      }

      renderer.Render();
    }
  } catch (std::exception& e) {
    Log::Error(e.what());
  }
  return 0;
}
